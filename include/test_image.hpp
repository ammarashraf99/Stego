#pragma once
#include "image.hpp"
#include <print>

class TestProcessImage {
public:
	TestProcessImage(Image<uint8_t> img)
	{
		int width = img.width();
		int height = img.height();
		std::println("size of vector should be {}, it is {}", width * height, pixs.size());

		img.mat().at<cv::Vec3b>(5, 10) = 'A';
		img.mat().at<cv::Vec3b>(10, 20) = 'B';
		img.mat().at<cv::Vec3b>(20, 30) = 'C';

	}



};
