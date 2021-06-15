# eos 的权限理解



## 权限

### 权限的赋予
* 权重: 一个公钥被授予的权限等级
* 门槛: 一个权限对公钥权重的要求
* 多签: 通过授予一个公钥低于门槛要求的权限，来控制公钥的行为；
即要求多个公钥共同签名来使得公钥权重之和>= 门槛要求，来共同完成一项操作；

权限是对私钥功能的一种限制

一个key可以被赋予多个权限

一个权限通过给与不同的key不同的权重来实现权力的分配和限制(多签...)

同一个key的不同权限无法通用

示例说明:
```shell
cli-baz set account permission usr miner '{"threshold": 1,
"keys": [{"key": "公钥","weight": 2}],"accounts": [{"permission":{"actor":"usr","permission":"active"},"weight":1}]}' owner -p usr@owner  
```

客户端代码:
```c++
struct set_account_permission_subcommand {
   string account;
   string permission;
   string authority_json_or_file;
   string parent;
   bool add_code = false;
   bool remove_code = false;

   set_account_permission_subcommand(CLI::App* accountCmd) {
      auto permissions = accountCmd->add_subcommand("permission", localized("set parameters dealing with account permissions"));
      //要被授予权限的账号
      permissions->add_option("account", account, localized("The account to set/delete a permission authority for"))->required();
      //权限名字
      permissions->add_option("permission", permission, localized("The permission name to set/delete an authority for"))->required();
      //被授予的权限json信息
      permissions->add_option("authority", authority_json_or_file, localized("[delete] NULL, [create/update] public key, JSON string or filename defining the authority, [code] contract name"));
      //父权限名，默认active
      permissions->add_option("parent", parent, localized("[create] The permission name of this parents permission, defaults to 'active'"));
      permissions->add_flag("--add-code", add_code, localized("[code] add '${code}' permission to specified permission authority", ("code", name(config::eosio_code_name))));
      permissions->add_flag("--remove-code", remove_code, localized("[code] remove '${code}' permission from specified permission authority", ("code", name(config::eosio_code_name))));

      add_standard_transaction_options(permissions, "account@active");

      permissions->callback([this] {
         EOSC_ASSERT( !(add_code && remove_code), "ERROR: Either --add-code or --remove-code can be set" );
         EOSC_ASSERT( (add_code ^ remove_code) || !authority_json_or_file.empty(), "ERROR: authority should be specified unless add or remove code permission" );

         authority auth;

         bool need_parent = parent.empty() && (name(permission) != name("owner"));
         bool need_auth = add_code || remove_code;

         if ( !need_auth && boost::iequals(authority_json_or_file, "null") ) {
            send_actions( { create_deleteauth(name(account), name(permission)) } );
            return;
         }

         if ( need_parent || need_auth ) {
            fc::variant json = call(get_account_func, fc::mutable_variant_object("account_name", account));
            auto res = json.as<eosio::chain_apis::read_only::get_account_results>();
            auto itr = std::find_if(res.permissions.begin(), res.permissions.end(), [&](const auto& perm) {
               return perm.perm_name == name(permission);
            });

            if ( need_parent ) {
               // see if we can auto-determine the proper parent
               if ( itr != res.permissions.end() ) {
                  parent = (*itr).parent.to_string();
               } else {
                  // if this is a new permission and there is no parent we default to "active"
                  parent = config::active_name.to_string();
               }
            }

            if ( need_auth ) {
               auto actor = (authority_json_or_file.empty()) ? name(account) : name(authority_json_or_file);
               auto code_name = config::eosio_code_name;

               if ( itr != res.permissions.end() ) {
                  // fetch existing authority
                  auth = std::move((*itr).required_auth);

                  auto code_perm = permission_level { actor, code_name };
                  auto itr2 = std::lower_bound(auth.accounts.begin(), auth.accounts.end(), code_perm, [&](const auto& perm_level, const auto& value) {
                     return perm_level.permission < value; // Safe since valid authorities must order the permissions in accounts in ascending order
                  });

                  if ( add_code ) {
                     if ( itr2 != auth.accounts.end() && itr2->permission == code_perm ) {
                        // authority already contains code permission, promote its weight to satisfy threshold
                        if ( (*itr2).weight < auth.threshold ) {
                           if ( auth.threshold > std::numeric_limits<weight_type>::max() ) {
                              std::cerr << "ERROR: Threshold is too high to be satisfied by sole code permission" << std::endl;
                              return;
                           }
                           std::cerr << localized("The weight of '${actor}@${code}' in '${permission}' permission authority will be increased up to threshold",
                                                  ("actor", actor)("code", code_name)("permission", permission)) << std::endl;
                           (*itr2).weight = static_cast<weight_type>(auth.threshold);
                        } else {
                           std::cerr << localized("ERROR: The permission '${permission}' already contains '${actor}@${code}'",
                                                  ("permission", permission)("actor", actor)("code", code_name)) << std::endl;
                           return ;
                        }
                     } else {
                        // add code permission to specified authority
                        if ( auth.threshold > std::numeric_limits<weight_type>::max() ) {
                           std::cerr << "ERROR: Threshold is too high to be satisfied by sole code permission" << std::endl;
                           return;
                        }
                        auth.accounts.insert( itr2, permission_level_weight {
                           .permission = { actor, code_name },
                           .weight = static_cast<weight_type>(auth.threshold)
                        });
                     }
                  } else {
                     if ( itr2 != auth.accounts.end() && itr2->permission == code_perm ) {
                        // remove code permission, if authority becomes empty by the removal of code permission, delete permission
                        auth.accounts.erase( itr2 );
                        if ( auth.keys.empty() && auth.accounts.empty() && auth.waits.empty() ) {
                           send_actions( { create_deleteauth(name(account), name(permission)) } );
                           return;
                        }
                     } else {
                        // authority doesn't contain code permission
                        std::cerr << localized("ERROR: '${actor}@${code}' does not exist in '${permission}' permission authority",
                                               ("actor", actor)("code", code_name)("permission", permission)) << std::endl;
                        return;
                     }
                  }
               } else {
                  if ( add_code ) {
                     // create new permission including code permission
                     auth.threshold = 1;
                     auth.accounts.push_back( permission_level_weight {
                        .permission = { actor, code_name },
                        .weight = 1
                     });
                  } else {
                     // specified permission doesn't exist, so failed to remove code permission from it
                     std::cerr << localized("ERROR: The permission '${permission}' does not exist", ("permission", permission)) << std::endl;
                     return;
                  }
               }
            }
         }

         if ( !need_auth ) {
            auth = parse_json_authority_or_key(authority_json_or_file);
         }

         send_actions( { create_updateauth(name(account), name(permission), name(parent), auth) } );
      });
   }
};
```

eos链对于赋权的验证
```c++
   void authorization_manager::check_updateauth_authorization( const updateauth& update,
                                                               const vector<permission_level>& auths
                                                             )const
   {
      EOS_ASSERT( auths.size() == 1, irrelevant_auth_exception,
                  "updateauth action should only have one declared authorization" );
      const auto& auth = auths[0];
      EOS_ASSERT( auth.actor == update.account, irrelevant_auth_exception,
                  "the owner of the affected permission needs to be the actor of the declared authorization" );

      const auto* min_permission = find_permission({update.account, update.permission});
      if( !min_permission ) { // creating a new permission
         min_permission = &get_permission({update.account, update.parent});
      }

      EOS_ASSERT( get_permission(auth).satisfies( *min_permission,
                                                  _db.get_index<permission_index>().indices() ),
                  irrelevant_auth_exception,
                  "updateauth action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                  ("auth", auth)("min", permission_level{update.account, min_permission->name}) );
   }
```


### 链接权限
一个key被授予了权限，且达到了门槛，并不意味着可以调用接口了，还需要将权限与接口绑定起来，才可以调用；

示例说明
```shell
cli-baz set action permission usr miner agreebind miner -p usr@owner
```

客户端代码:
```c++
struct set_action_permission_subcommand {
   string accountStr;
   string codeStr;
   string typeStr;
   string requirementStr;

   set_action_permission_subcommand(CLI::App* actionRoot) {
      auto permissions = actionRoot->add_subcommand("permission", localized("set parmaters dealing with account permissions"));
      permissions->add_option("account", accountStr, localized("The account to set/delete a permission authority for"))->required();
      permissions->add_option("code", codeStr, localized("The account that owns the code for the action"))->required();
      permissions->add_option("type", typeStr, localized("the type of the action"))->required();
      permissions->add_option("requirement", requirementStr, localized("[delete] NULL, [set/update] The permission name require for executing the given action"))->required();

      add_standard_transaction_options(permissions, "account@active");

      permissions->callback([this] {
         name account = name(accountStr);
         name code = name(codeStr);
         name type = name(typeStr);
         bool is_delete = boost::iequals(requirementStr, "null");

         if (is_delete) {
            send_actions({create_unlinkauth(account, code, type)});
         } else {
            name requirement = name(requirementStr);
            send_actions({create_linkauth(account, code, type, requirement)});
         }
      });
   }
};
```

eos链对于链接的验证
```c++
void authorization_manager::check_linkauth_authorization( const linkauth& link,
                                                             const vector<permission_level>& auths
                                                           )const
   {
      EOS_ASSERT( auths.size() == 1, irrelevant_auth_exception,
                  "link action should only have one declared authorization" );
      const auto& auth = auths[0];
      EOS_ASSERT( auth.actor == link.account, irrelevant_auth_exception,
                  "the owner of the linked permission needs to be the actor of the declared authorization" );

      if( link.code == config::system_account_name
            || !_control.is_builtin_activated( builtin_protocol_feature_t::fix_linkauth_restriction ) ) 
      {
         EOS_ASSERT( link.type != updateauth::get_name(),  action_validate_exception,
                     "Cannot link eosio::updateauth to a minimum permission" );
         EOS_ASSERT( link.type != deleteauth::get_name(),  action_validate_exception,
                     "Cannot link eosio::deleteauth to a minimum permission" );
         EOS_ASSERT( link.type != linkauth::get_name(),    action_validate_exception,
                     "Cannot link eosio::linkauth to a minimum permission" );
         EOS_ASSERT( link.type != unlinkauth::get_name(),  action_validate_exception,
                     "Cannot link eosio::unlinkauth to a minimum permission" );
         EOS_ASSERT( link.type != canceldelay::get_name(), action_validate_exception,
                     "Cannot link eosio::canceldelay to a minimum permission" );
      }

      const auto linked_permission_name = lookup_minimum_permission(link.account, link.code, link.type);

      if( !linked_permission_name ) // if action is linked to eosio.any permission
         return;

      EOS_ASSERT( get_permission(auth).satisfies( get_permission({link.account, *linked_permission_name}),
                                                  _db.get_index<permission_index>().indices()              ),
                  irrelevant_auth_exception,
                  "link action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                  ("auth", auth)("min", permission_level{link.account, *linked_permission_name}) );
   }
```