#pragma once

#include <cstdlib>
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


void stego(const cxxopts::Options& options, const cxxopts::ParseResult& result);
void resolve_options(const cxxopts::Options& options, const cxxopts::ParseResult& result,
		     std::string& input, std::string& output, std::string& mode,
		     std::string& data, std::string& help);
