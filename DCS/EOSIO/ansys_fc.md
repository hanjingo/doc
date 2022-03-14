# Eos源码分析-fc

[TOC]



## 摘要



## 详情

### 定义全局函数
#### fc
|定义|注释|
|:---|:---|
|std::string smaz_compress( const std::string& in )|?|
|std::string smaz_decompress( const::string& compressed )|?|

#### fc::raw::detail
|定义|注释|
|:---|:---|
|inline void pack_set( Stream& s, const Set<T, U...>& value )|打包set类型数据|
|inline void unpack_set( Stream& s, Set<T, u...>& value)|解包set类型数据|
|inline void unpack_flat_set( Stream& s, Set<T, U...>& value )|解包一段set类型数据|
|inline void pack_map( Stream& s, const Map<K, V, U...>& value )|打包map类型数据|
|inline void unpack_map( Stream& s, Map<K, V, U...>& value )|解包map类型数据|
|inline void unpack_flat_map( Stream& s, Map<K, V, U...>& value )|解包一段map类型数据|

#### fc::detail
|定义|注释|
|:---|:---|
|void to_variant_from_set( const Set<T, U...>& s, fc::variant& vo|将set类型数据转到variant|
|void from_variant_to_set( const fc::variant& v, Set<T, U...>& s )|将variant类型数据转set|
|void from_variant_to_flat_set( const fc::variant& v, Set<T, U...>& s )|将variant类型数据转一段set|
|void to_variant_from_map( const Map<K, V, U...>& m, fc::variant& vo )|将map类型数据转variant|
|void from_variant_to_map( const variant& v, Map<K, V, U...>& m )|将variant类型数据转map|
|void from_variant_to_flat_map( const variant& v, Map<K, V, U...>& m )|将variant类型转一段map|

#### fc:raw
|定义|注释|
|:---|:---|
|void pack( Stream& s, const std::deque<T>& value )|打包|
|void unpack( Stream& s, std::deque<T>& value )|解包|

#### fc
|定义|注释|
|:---|:---|
|unsigned aes_encrypt(unsigned char *plaintext, int plaintext_len, usigned char *key, unsigned char *iv, unsigned char *ciphertext)|?|
|unsigned aes_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)|?|
|unsigned aes_cfb_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char*plaintext)|?|
|std::vector<char> aes_encrypt( const fc::sha512& key, const std::vector<char>& plain_text )|?|
|std::vector<char> aes_decrypt( const fc::sha512& key, const std::vector<char>& cipher_text )|?|
|void aes_save( const fc::path& file, const fc::sha512& key, std::vector<char> plain_text )|?|
|std::vector<char> aes_load( const fc::path& file, const fc::sha512& key )|?|

### 定义类
#### aes_encoder
|类型|名称|注释|
|:---|:---|:---|
|public func|void init( const fc::sha256& key, const fc::uint128& init_value )|初始化|
|public func|uint32_t encode( const char* plaintxt, uint32_t len, char* ciphertxt )|编码|
|private struct|impl|?|?|
|private fc::fwd<impl, 96>|my|?|

#### fc::aes_decoder
|类型|名称|注释|
|:---|:---|:---|
|public func|init( const fc::sha256& key, const fc::uint128& init_value )|初始化|
|public func|decode( const char* ciphertxt, uint32_t len, char* plaintext )|解码|
|private struct|impl|?|
|private fc::fwd<impl, 96>|my|?|
