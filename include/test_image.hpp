#pragma once
#include "image.hpp"
#include <opencv2/imgcodecs.hpp>
#include <print>

class TestProcessImage {
public:
	TestProcessImage(Image img, std::string output)
	{
		for (int y {}; y < img.height(); ++y) {
			for (int x {}; x < img.width(); ++x) {
				img.mat().at<cv::Vec3b>(y, x)[2] = 0; // blue pixel is zerod
			}
		}
		bool success = cv::imwrite(output, img.mat());
		if (!success) {
			throw "Error writing to out image\n";
		}
	}


	void test_compare(std::string input, std::string output)
	{

	}



};
