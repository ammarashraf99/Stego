#pragma once
#include "image.hpp"
#include <opencv2/imgcodecs.hpp>
#include <print>

class TestProcessImage {
public:
	TestProcessImage(Image img, std::string output)
	{
		int width = img.width();
		int height = img.height();
		
		img.mat().at<uint8_t>(5, 10) = static_cast<int>('A');
		img.mat().at<uint8_t>(10, 20) = static_cast<int>('B');
		img.mat().at<uint8_t>(20, 30) = static_cast<int>('C');

		try {
			if (img.channels() != 3) {
				throw "crazy channel number\n";
			}
			std::println("channel length is {}", img.channels());
		} catch (const char* mess) {
			std::println("Error: {}", mess);
			std::abort();
		}

		std::println("channel length is {}", img.channels());

		try {
			if (img.depth() == -1) {
				throw "Undefined depth\n";
			}
		}
		catch (const char* mess) {
			std::println("Error: {}", mess);
			std::abort();
		}



		bool success = cv::imwrite(output, img.mat());
		if (!success) {
			throw "error writing to new image\n";
		}

	}


	void test_compare(std::string input, std::string output)
	{
		cv::Mat input_mat = cv::imread(input);
		cv::Mat output_mat = cv::imread(output);

		if (output_mat.at<uint8_t>(5, 10) != input_mat.at<uint8_t>(5, 10) &&
		    output_mat.at<uint8_t>(10, 20) != input_mat.at<uint8_t>(5, 10) &&
		    output_mat.at<uint8_t>(20, 30) != input_mat.at<uint8_t>(5, 10) ) {
			std::println("\nThe output & input arrays are verified to be not equal at target points\n");
		}

		if (output_mat.at<uint8_t>(6, 11) == input_mat.at<uint8_t>(5, 10) &&
		    output_mat.at<uint8_t>(11, 21) == input_mat.at<uint8_t>(5, 10) &&
		    output_mat.at<uint8_t>(21, 31) == input_mat.at<uint8_t>(5, 10) ) {
			std::println("The output & input are verified to be equal otherwise\n");
		}

		if (output_mat.at<uint8_t>(5, 10) == static_cast<int>('A')  &&
		    output_mat.at<uint8_t>(10, 20) == static_cast<int>('B') &&
		    output_mat.at<uint8_t>(20, 30) == static_cast<int>('C') ) {

			std::println("The output array is verified to be modireid right\n");
		}


		


	}



};
