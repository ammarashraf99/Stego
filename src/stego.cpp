#include "stego.hpp"


void stego(const cxxopts::Options& options, const cxxopts::ParseResult& result)
{

	if (result.count("help")) {
		std::println("{}", options.help());
		std::exit(0);
	}

	if (!result.count("mode")) {
		std::println("[Usage]: Please enter a mode");
		std::exit(0);
	}

	/* three must have options */
	if ( !(result.count("mode") && result.count("input") && result.count("data")) ) {
		std::println("[Usage]: missing option/s");
		std::exit(1);
	}

	std::string mode   = result["mode"].as<std::string>();
	std::string input  = result["input"].as<std::string>();
	std::string dataFile   = result["data"].as<std::string>();

	Image img(input);
	
	std::unique_ptr<Embedder> embedder { std::make_unique<LSB_Embedder>()};
	
	if (mode == "embed") {
		if (! result.count("output")) {
			std::println("[Usage]: missing option --output");
			std::exit(1);
		}
		std::string output = result["output"].as<std::string>();
		std::ifstream ifs(dataFile, std::ios::binary);
		if (!ifs.is_open()) {
			std::println("[ERROR]: opening data file");
			std::exit(1);
		}
		/* slurpe file in into a vector */
		std::vector<uint8_t> payload_in((std::istreambuf_iterator<char>(ifs)), 
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
		std::println("[Usage]: wrong mode");
		std::exit(1);
	}
}
