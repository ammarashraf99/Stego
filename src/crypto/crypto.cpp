#include "crypto.hpp"
// private includes
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

Cipher::Cipher(const std::string& password)
{
	_key = derive_key(password);
}

Cipher::Cipher(const std::string& password, const std::vector<uint8_t>& iv, const std::vector<uint8_t>& salt) 
	:_iv(iv), _salt(salt)
{
	_key = derive_key(password, _salt);
}

std::vector<uint8_t> Cipher::encrypt(const std::vector<uint8_t>& plaintext)
{
	_iv.resize(IV_LEN);
	RAND_bytes(_iv.data(), IV_LEN);

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	if (!ctx) handleErrors("Failed to create cipher ctx");

	if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, _key.data(), _iv.data()) != 1)
		handleErrors("EncryptInit failed");

	std::vector<uint8_t> ciphertext(plaintext.size() + IV_LEN);
	int len = 0, ciphertext_len = 0;
	if (EVP_EncryptUpdate(ctx,
			      ciphertext.data(), &len,
			      reinterpret_cast<const uint8_t*>(plaintext.data()),
			      plaintext.size()) != 1)
		handleErrors("EncryptUpdate failed");

	ciphertext_len = len;
	if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
		handleErrors("EncryptFinal failed");

	ciphertext_len += len;
	ciphertext.resize(ciphertext_len);
	EVP_CIPHER_CTX_free(ctx);
	
	return ciphertext;
}


std::vector<uint8_t> Cipher::decrypt(const std::vector<uint8_t>& cipher_text)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors("Failed to create cipher ctx");

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, _key.data(), _iv.data()) != 1)
	    handleErrors("DecryptInit failed");
    
    std::vector<uint8_t> plain_text(cipher_text.size());
    int len = 0, plain_text_len = 0;

    if (EVP_DecryptUpdate(ctx,
                          plain_text.data(), &len,
                          cipher_text.data(), cipher_text.size()) != 1)
	    handleErrors("DecryptUpdate failed");

    plain_text_len = len;

    if (EVP_DecryptFinal_ex(ctx, plain_text.data() + len, &len) != 1)
	    handleErrors("DecryptFinal failed");

    plain_text_len += len;
    plain_text.resize(plain_text_len);

    EVP_CIPHER_CTX_free(ctx);

    return plain_text;
}

void Cipher::add_salt_iv(std::vector<uint8_t>& cipher_text)
{
	cipher_text.insert(cipher_text.end(), _salt.begin(), _salt.end());
	cipher_text.insert(cipher_text.end(), _iv.begin(), _iv.end());
}

std::vector<uint8_t> Cipher::derive_key(const std::string& password) // will generate iv, salt
{
	_salt.resize(SALT_LEN);
	RAND_bytes(_salt.data(), SALT_LEN);

	return derive_key(password, _salt);
}

std::vector<uint8_t> Cipher::derive_key(const std::string& password,
					std::vector<uint8_t>& salt)
{
	std::vector<uint8_t> key(KEY_LEN);
	if (PKCS5_PBKDF2_HMAC(password.c_str(), password.size(),
			      salt.data(), SALT_LEN, PBKDF2_ITERS,
			      EVP_sha256(), KEY_LEN, key.data()) != 1) {
		handleErrors("Key derivation failed");
	}
	return key;
}

void Cipher::handleErrors(const std::string& msg) {
	throw std::runtime_error(msg);
}
