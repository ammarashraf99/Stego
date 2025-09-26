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

	cxxopts::ParseResult result;
	try {
		result = options.parse(argc, argv);
	} catch (cxxopts::exceptions::no_such_option ex) {
		std::println("[Usage] {}", ex.what());
		std::exit(0);
	}
	try {
		stego(options, result);
	} catch (const char* mess) {
		std::println("[ERROR] {}", mess);
		std::exit(1);
	}
	std::exit(0);
}
