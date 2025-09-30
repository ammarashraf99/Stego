#pragma once
#include <iostream>
#include <vector>

class Cipher {
public:
	Cipher(const std::string& password);
	Cipher(const std::string& password, const std::vector<uint8_t>& iv, const std::vector<uint8_t>& salt);
	std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plain_text);
	std::vector<uint8_t> decrypt(const std::vector<uint8_t>& cipher_text);
	void add_salt_iv(std::vector<uint8_t>& cipher_text);

private:
	std::vector<uint8_t> derive_key(const std::string& password); // will generate iv, salt
	std::vector<uint8_t> derive_key(const std::string& password,
					std::vector<uint8_t>& salt);
	void handleErrors(const std::string& msg);

public:
	static const int IV_LEN = 16;
	static const int SALT_LEN = 16;

private:
	static const int KEY_LEN = 32;
	static const int PBKDF2_ITERS = 100000;

	std::vector<uint8_t> _key;
	std::vector<uint8_t> _iv;
	std::vector<uint8_t> _salt;

};
