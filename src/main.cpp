#include <iostream>
#include <cxxopts.hpp>

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

	std::cout << "Mode: " << mode
		  << " Input: " << input
		  << " Output: " << output << "\n";
}
