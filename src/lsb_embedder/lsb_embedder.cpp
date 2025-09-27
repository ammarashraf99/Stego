#include "lsb_embedder.hpp"
// private includes
#include "crypto.hpp"
#include <stdexcept>

void LSB_Embedder::next_pixel(const Image& img, std::pair<int, int>& pos)
{
	static int row_step {img.width() / 30};
	if (pos.second == row_step * 24) { // last step in row, 24 steps * 1 bits = 24bits (3bytes per row)
		pos.first++;
		pos.second = 0;
	} else {
		pos.second += row_step;
	}
}

void LSB_Embedder::embed(Image& img, const std::vector<uint8_t>& data)
{
	std::pair<int, int> pos {}; // height, width
	size_t file_size;
	bool bit_is_set{};
	
	std::string password;
	std::print("please enter a password : ");
	std::cin >> password;

	Cipher cipher(password);
	std::vector<uint8_t> cipher_text { cipher.encrypt(data) };
	cipher.add_salt_iv(cipher_text);
	file_size = cipher_text.size();

	for (int j {sizeof(size_t)}; j >= 0; --j) { // embed size
		uint8_t byte { static_cast<uint8_t>( file_size>>(j*7) ) };
		for (int i {7}; i >= 0; --i) {
			bit_is_set = (byte >> i) & 1;
			if (bit_is_set) {
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] |= 1;
			} else {
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%img.channels()] &= ~1;
			}
			next_pixel(img, pos);
		}
	}
	
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

std::vector<uint8_t> LSB_Embedder::extract(const Image& img)
{
	std::vector<uint8_t> cipher_text;
	std::pair<int, int> pos {};
	bool bit_is_set {};

	size_t file_size {};

	for (int j {sizeof(size_t)}; j >= 0; --j) { // extract size
		uint8_t byte {};
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
		file_size = static_cast<size_t>( byte << (j*7) );
	}

	for (int j {}; j < file_size; ++j) {
		uint8_t byte {};
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
		cipher_text.push_back(byte);
	}

	std::vector<uint8_t> iv ( cipher_text.begin() + (cipher_text.size() - Cipher::IV_LEN),
				  cipher_text.end());
	cipher_text.resize(cipher_text.size() - Cipher::IV_LEN);
	std::vector<uint8_t> salt( cipher_text.begin() + (cipher_text.size() - Cipher::SALT_LEN),
				  cipher_text.end());
	cipher_text.resize(cipher_text.size() - Cipher::SALT_LEN);

	std::string password;
	std::print("please enter a password : ");
	std::cin >> password;

	Cipher cipher(password, iv, salt);
	std::vector<uint8_t> plain_text;
	try {
		plain_text = cipher.decrypt(cipher_text);
	} catch(std::runtime_error mes) {
		std::println("{}", mes.what());
		std::println("Please try again");
		exit(1);
	}

	return plain_text;
}

