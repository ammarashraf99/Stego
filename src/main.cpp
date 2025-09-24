#include "stego.hpp"

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
	stego(options, result);
	std::exit(0);
}
