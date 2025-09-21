#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <print>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cxxopts.hpp>
#include "image.hpp"
#include "test_image.hpp"

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


	Image img(input);
	TestProcessImage test_image(img, output);


}
