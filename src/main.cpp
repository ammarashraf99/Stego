#include <iterator>
#include <print>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cxxopts.hpp>
#include <memory>
#include <fstream>
#include "image.hpp"
#include "embedder.hpp"
#include "lsb_embedder.hpp"

int main(int argc, char* argv[])
{
	cxxopts::Options options("stego", "Steganography tool");

	options.add_options()
		("i,input", "Input image",              cxxopts::value<std::string>())
		("o,output", "Output image",            cxxopts::value<std::string>())
		("m,mode", "Mode: embed or extract",    cxxopts::value<std::string>())
		("d,data", "Data file (for embedding)", cxxopts::value<std::string>())
		("h,help", "Print usage");

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::println("{}", options.help());
		return 0;
	}

	std::string input  = result["input"].as<std::string>();
	std::string output = result["output"].as<std::string>();
	std::string mode   = result["mode"].as<std::string>();
	std::string dataFile   = result["data"].as<std::string>();

	Image img(input);

	std::unique_ptr<Embedder> embedder { std::make_unique<LSB_Embedder>()};
	
	if (mode == "embed") {
		std::ifstream ifs (input, std::ios::binary);
		if (!ifs.is_open()) {
			std::println("Error opening data file");
			std::abort();
		}
		std::vector<uint8_t> payload_in((std::istreambuf_iterator<char>(ifs)),  // slurpe file in one go
					     (std::istreambuf_iterator<char>()));
		embedder->embed(img, payload_in);
		img.save(output);
	} else if (mode == "extract") {
		std::vector<uint8_t> payload_out;
		payload_out = embedder->extract(img);
		std::ofstream ofs(dataFile, std::ios::binary);
		/* dumping the vector to the file */
		ofs.write(reinterpret_cast<char*>(payload_out.data()), payload_out.size());
	} else {
		std::println("wrong mode");
		std::abort();
	}
}
