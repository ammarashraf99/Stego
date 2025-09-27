#pragma once
#include "embedder.hpp"
#include <iostream>
#include "image.hpp"
#include <print>

class LSB_Embedder : public Embedder{
public:
	LSB_Embedder() = default;
	void embed(Image& img, const std::vector<uint8_t>& data) override;
	std::vector<uint8_t> extract(const Image& img) override;
private:
	void next_pixel(const Image& img, std::pair<int, int>& pos);
	void embed_size(std::pair<int, int>& pos, Image& img, const size_t& file_size);
	void embed_cipher_text(std::pair<int, int>& pos, Image& img, const size_t& file_size,
			       const std::vector<uint8_t>& cipher_text);
	void extract_size(std::pair<int, int>& pos, const Image& img, size_t& file_size);
	void extract_cipher(std::pair<int, int>& pos, const Image& img, const size_t& file_size,
			    std::vector<uint8_t>& cipher_text);

};
