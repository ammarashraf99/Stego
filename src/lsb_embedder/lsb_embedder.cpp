#include "lsb_embedder.hpp"
// private includes
#include "crypto.hpp"


void LSB_Embedder::embed(Image& img, const std::vector<uint8_t>& data)
{
	std::pair<int, int> pos {}; // height, width
	size_t cipher_text_size;
	std::string password;
	size_t max_img_cap {static_cast<size_t>(((img.height() * (img.width() - 1)) - sizeof(size_t)) / 8)};

	std::println("[INFO] image max capacity is {} bytes", max_img_cap);
	std::print("[INFO] please enter a password : ");
	std::cin >> password;

	Cipher cipher(password);
	std::vector<uint8_t> cipher_text { cipher.encrypt(data) };
	cipher.add_salt_iv(cipher_text);
	cipher_text_size = cipher_text.size();
	std::println("[INFO] cipher text size is {} bytes", cipher_text_size);
	if (cipher_text_size > max_img_cap)  {
		std::println("[Usage] too large input file to embed");
		exit(1);
	}

	embed_size(pos, img, cipher_text_size);
	embed_cipher_text(pos, img, cipher_text_size, cipher_text);
}

std::vector<uint8_t> LSB_Embedder::extract(const Image& img)
{
	std::pair<int, int> pos {};
	std::vector<uint8_t> cipher_text;
	size_t cipher_text_size {};
	std::string password;
	size_t max_img_cap {static_cast<size_t>(((img.height() * (img.width() - 1)) - sizeof(size_t)) / 8)};

	std::println("[INFO] image max capacity is {} bytes", max_img_cap);

	extract_size(pos, img, cipher_text_size);
	cipher_text.resize(cipher_text_size);
	extract_cipher(pos, img, cipher_text_size, cipher_text);

	std::vector<uint8_t> iv ( cipher_text.begin() + (cipher_text.size() - Cipher::IV_LEN),
				  cipher_text.end());
	cipher_text.resize(cipher_text.size() - Cipher::IV_LEN);
	std::vector<uint8_t> salt( cipher_text.begin() + (cipher_text.size() - Cipher::SALT_LEN),
				  cipher_text.end());
	cipher_text.resize(cipher_text.size() - Cipher::SALT_LEN);

	std::print("[INFO] please enter a password : ");
	std::cin >> password;

	Cipher cipher(password, iv, salt);
	std::vector<uint8_t> plain_text;
	try {
		plain_text = cipher.decrypt(cipher_text);
	} catch(std::runtime_error mes) {
		std::println("[ERROR] {}", mes.what());
		std::println("[INFO] Please try again");
		exit(1);
	}

	return plain_text;
}

void LSB_Embedder::next_pixel(const Image& img, std::pair<int, int>& pos)
{
	if (pos.second == img.width()) {
		pos.first++;
		pos.second = 0;
	} else {
		pos.second++; 
	}
}

void LSB_Embedder::embed_size(std::pair<int, int>& pos, Image& img, const size_t& file_size)
{
	bool bit_is_set{};
	size_t bit_counter {sizeof(size_t) - 1};

	for (int j { sizeof(size_t) - 1 }; j >= 0; --j) {
		for (int i {7}; i >= 0; --i) {
			bit_is_set = (file_size >> bit_counter--) & 1;
			if (bit_is_set) {
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] |= 1;
			} else {
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] &= ~1;
			}
			next_pixel(img, pos);
		}
	}
}

void LSB_Embedder::embed_cipher_text(std::pair<int, int>& pos, Image& img, const size_t& file_size,
		       const std::vector<uint8_t>& cipher_text)
{
	bool bit_is_set {};

	for (auto& byte: cipher_text) {
		for (int i {7}; i >= 0; --i) {
			bit_is_set = (byte >> i) & 1;
			if (bit_is_set) {
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] |= 1; // set lsb
			} else {
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] &= ~1; // clear lsb
			}
			next_pixel(img, pos);
		}
	}
}

void LSB_Embedder::extract_size(std::pair<int, int>& pos, const Image& img, size_t& file_size)
{
	bool bit_is_set {};
	size_t bit_counter {sizeof(size_t) - 1};

	for (int j {sizeof(size_t) - 1}; j >= 0; --j) {
		for (int i {7}; i >= 0; --i) {
			bit_is_set = img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] & 1;
			if (bit_is_set) {
				file_size |= (static_cast<size_t>(1)<<bit_counter--);
			} else {
				file_size &= ~(static_cast<size_t>(1)<<bit_counter--);
			}
			next_pixel(img, pos);
		}
	}
}

void LSB_Embedder::extract_cipher(std::pair<int, int>& pos, const Image& img, const size_t& file_size,
		    std::vector<uint8_t>& cipher_text)
{
	bool bit_is_set {};

	for (auto& byte: cipher_text) {
		for (int i {7}; i >= 0; --i) {
			byte = (byte << 1);
			bit_is_set = img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] & 1;
			if (bit_is_set) {
				byte |= 1;
			} else {
				byte &= ~1;
			}
			next_pixel(img, pos);
		}
	}
}
