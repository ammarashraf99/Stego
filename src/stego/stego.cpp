#include "stego.hpp"

void stego(const cxxopts::Options& options, const cxxopts::ParseResult& result)
{
	std::string input;
	std::string output;
	std::string mode;
	std::string data;
	std::string help;

	resolve_options(options, result, input, output, mode, data, help);

	Image img(input);
	
	std::unique_ptr<Embedder> embedder { std::make_unique<LSB_Embedder>()};
	
	if (mode == "embed") {
		std::ifstream ifs(data, std::ios::binary);
		if (!ifs.is_open()) {
			throw "can't open input data file";
			std::exit(1);
		}
		std::println("[INFO] Loading input file...");
		/* slurpe file in into a vector */
		std::vector<uint8_t> payload_in((std::istreambuf_iterator<char>(ifs)), 
						(std::istreambuf_iterator<char>()));
		std::println("[INFO] Embeding Data file...");
		embedder->embed(img, payload_in);
		img.save(output);

	} else if (mode == "extract") {
		std::vector<uint8_t> payload_out; 
		std::println("[INFO] Extracting data...");
		payload_out = embedder->extract(img);
		std::println("[INFO] Writing data to file...");
		std::ofstream ofs(data, std::ios::binary);
		/* dumping the vector to the file */
		ofs.write(reinterpret_cast<char*>(payload_out.data()), payload_out.size());
	}
}



void resolve_options(const cxxopts::Options& options, const cxxopts::ParseResult& result,
		     std::string& input, std::string& output, std::string& mode,
		     std::string& data, std::string& help)
{
	std::queue<std::string> missed;
	if (result.count("help")) {
		std::println("{}", options.help());
		std::exit(0);
	}
	if (!result.count("mode")) {
		std::println("[Usage] Please enter a mode");
		std::exit(0);
	}
	
	mode   = result["mode"].as<std::string>();
	
	if (mode == "embed") {
		if (result.count("input")) {
			input = result["input"].as<std::string>();
		} else {
			missed.push("input");
		}
		if (result.count("output")) {
			output = result["output"].as<std::string>();
		} else {
			missed.push("output");
		}
		if (result.count("data")) {
			data = result["data"].as<std::string>();
		} else {
			missed.push("data");
		}
	} else if (mode == "extract"){
		if (result.count("input")) {
			input = result["input"].as<std::string>();
		} else {
			missed.push("input");
		}
		if (result.count("data")) {
			data = result["data"].as<std::string>();
		} else {
			missed.push("data");
		}
	} else {
		std::println("[Usage] no such mode");
		std::exit(0);
	}

	if (!missed.empty()) {
		std::print("[Usage] missing options ");
		while(!missed.empty()) {
			std::print("--{} ", missed.front());
			missed.pop();
		}
		std::println("");
		std::exit(0);
	}
}
