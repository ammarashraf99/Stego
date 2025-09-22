#pragma once
#include "embedder.hpp"

class LSB_Embedder : public Embedder{
public:
	LSB_Embedder() = default;
	void embed(Image& img, const std::vector<uint8_t>& data) override;
	std::vector<uint8_t> extract(const Image& img) override;
};
