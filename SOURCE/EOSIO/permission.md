# 摘要
对一些权限操作的封装

# 详情
[permission.hpp]()

## 导出c函数 具体看eos的wasm_interface.cpp
|定义|说明|
|:---|:---|
|int32_t check_transaction_authorization( const char*, uint32_t, const char*, uint32_t, const char*, uint32_t )|检查传输权限|
|int32_t check_permission_authorization( uint64_t, uint64_t, const char*, uint32_t, const char*, uint32_t, uint64_t )|检查验证权限|
|int64_t get_permission_last_used(uint64_t, uint64_t)|获得最后一次使用该权限的时间|
|int64_t get_account_creation_time(uint64_t)|获得账号创建的时间|
