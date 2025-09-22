#pragma once
#include "image.hpp"

// abstract embedder
class Embedder {
public:
	Embedder() = default;
	virtual ~Embedder() = default;
	virtual void embed(Image& img, const std::vector<uint8_t>& data) = 0;
	virtual std::vector<uint8_t> extract(const Image& img) = 0;
};
