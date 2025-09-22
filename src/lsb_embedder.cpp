#include "lsb_embedder.hpp"

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
	std::pair<int, int> pos{}; // height, width
	
	for (auto byte: data) {

		for (size_t i {7}; i >= 0; --i) {

			/* B lsb pixel*/
			(img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%3] & 1) | 0 ?
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%3] |= (byte >> i) & 1 : // lsb is 1
				img.mat().at<cv::Vec3b>(pos.first, pos.second)[i%3] &= (byte >> i) & 1;  // lsb is 0
			
			next_pixel(img, pos);
		}
	}
}



