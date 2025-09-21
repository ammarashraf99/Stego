#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <print>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cxxopts.hpp>
#include "image.hpp"

int main(int argc, char* argv[])
{
	cxxopts::Options options("stego", "Steganography tool");

	options.add_options()
		("i,input", "Input image", cxxopts::value<std::string>())
		("o,output", "Output image", cxxopts::value<std::string>())
		("m,mode", "Mode: embed or extract", cxxopts::value<std::string>())
		("h,help", "Print usage");

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << "\n";
		return 0;
	}

	std::string input  = result["input"].as<std::string>();
	std::string output = result["output"].as<std::string>();
	std::string mode   = result["mode"].as<std::string>();


	// cv::Mat image = cv::imread(input); // don't need the alpha channel
	// std::println("depth is {}", [](int en){
	// 	switch (en) {
	// 	case CV_8U:
	// 	case CV_8S:
	// 		return 8;
	// 	case CV_16U:
	// 	case CV_16S:
	// 		return 16;
	// 	case CV_32S:
	// 	case CV_32F:
	// 		return 32;
	// 	default:
	// 		return -1;
			
	// 	}
	// }(image.depth()));

	// std::println("channels are {}", image.channels());
	// std::println("rows are {}", image.rows);
	// std::println("cols are {}", image.cols);

	// cv::Vec3b nigga; // b byte, d double, f float, w word

	// cv::Vec3b pixel = img.at<cv::Vec3b>(20, 10); // (y, x)
	//    std::cout << "Pixel(10,20): B=" << (int)pixel[0]
	//              << " G=" << (int)pixel[1]
	//              << " R=" << (int)pixel[2] << "\n";




	/** show an image **/
	// cv::namedWindow("Image");
	// cv::imshow("Image", image);
	// cv::waitKey(0);
	// cv::destroyWindow("Image");
}
