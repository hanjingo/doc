# openssl - DES使用示例

[TOC]



## ECB模式

### 例1 ECB模式下正确性及性能测试

(以下代码基于vs2015 + openssl 1.1.1)

```c++
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <openssl/des.h>

#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")

// 加密ecb模式
std::string desEncrypt(const std::string &clearText, const std::string &key)
{
	std::string cipherText; // 密文

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	// 构造补齐后的密钥
	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	// 密钥置换
	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	// 循环加密，每8字节一次
	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCiphertext;
	vecCiphertext.reserve(clearText.length());
	unsigned char tmp[8];

	for (auto i = 0; i < clearText.length() / 8; i++)
	{
		memcpy(inputText, clearText.c_str() + i * 8, 8);
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		vecCiphertext.reserve(vecCiphertext.size() + 8);
		for (auto j = 0; j < 8; j++)
			vecCiphertext.emplace_back(tmp[j]);
	}

	if (clearText.length() % 8 != 0)
	{
		auto tmp1 = clearText.length() / 8 * 8;
		auto tmp2 = clearText.length() - tmp1;
		memset(inputText, 0, 8);
		memcpy(inputText, clearText.c_str() + tmp1, tmp2);
		// 加密函数
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		vecCiphertext.reserve(vecCiphertext.size() + 8);
		for (auto j = 0; j < 8; j++)
			vecCiphertext.emplace_back(tmp[j]);
	}

	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}

// 解密ecb模式
std::string desDecrypt(const std::string &cipherText, const std::string &key)
{
	std::string clearText; // 明文

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCleartext;
	vecCleartext.reserve(cipherText.length());
	unsigned char tmp[8];

	for (auto i = 0; i < cipherText.length() / 8; i++)
	{
		memcpy(inputText, cipherText.c_str() + i * 8, 8);
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
		memcpy(tmp, outputText, 8);

		for (auto j = 0; j < 8; j++)
			vecCleartext.emplace_back(tmp[j]);
	}

	if (cipherText.length() % 8 != 0)
	{
		auto tmp1 = cipherText.length() / 8 * 8;
		auto tmp2 = cipherText.length() - tmp1;
		memset(inputText, 0, 8);
		memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
		// 解密函数
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
		memcpy(tmp, outputText, 8);

		vecCleartext.reserve(vecCleartext.size() + 8);
		for (auto j = 0; j < 8; j++)
			vecCleartext.emplace_back(tmp[j]);
	}

	clearText.clear();
	clearText.assign(vecCleartext.begin(), vecCleartext.end());

	return clearText;
}

int main(int argc, char **argv)
{
	std::string srcText = "hello world";

	std::string encryptText;
	std::string decryptText;
	std::string key{ "12345" };

	std::cout << "des - ecb加/解密正确性测试" << std::endl;
	std::cout << "加密前:" << srcText << std::endl;
	encryptText = desEncrypt(srcText, key);
	std::cout << "加密后:" << encryptText << std::endl;
	decryptText = desDecrypt(encryptText, key);
	std::cout << "解密后:" << decryptText << std::endl;

	std::cout << "\ndes - ecb加/解密性能测试" << std::endl;
	auto n = 100000;
	auto startTime = std::chrono::system_clock::now();
	for (auto i = 0; i < n; i++)
		desDecrypt(desEncrypt(srcText, key), key);
	auto endTime = std::chrono::system_clock::now();
	auto durSec = std::chrono::duration_cast<std::chrono::duration<double> >(
		          endTime.time_since_epoch() - startTime.time_since_epoch()).count();
	std::cout << "连续运行: " << n << " 次加解密，共耗时:" << durSec << "s" << std::endl;

	system("pause");
	return 0;
}
```

### 例2 ECB模式下加/解密文件

(以下代码基于vs2015 + openssl 1.1.1)

TODO



## 参考

[1] [C/C++使用openssl进行摘要和加密解密（md5, sha256, des, rsa](https://blog.csdn.net/u012234115/article/details/72762045)

