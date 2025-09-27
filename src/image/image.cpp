#include "image.hpp"

Image::Image(const std::string& path)
{
	std::println("[INFO] Loading input image...");
	_mat = cv::imread(path, cv::IMREAD_UNCHANGED);

	if (_mat.empty())
		throw "can't loading image(cv::mat)";

	_width = _mat.cols;
	_height = _mat.rows;

	_depth = [](int en) {
		switch (en) {
		case CV_8U:
			return 8;
		case CV_16U:
			return 16;
		case CV_32F:
			return 32;
		default:
			return -1;
		}
	}(_mat.depth());

	_channels = _mat.channels();
}

void Image::save(const std::string& file_path) const 
{
	std::println("[INFO] Saving output image...");
	bool success = cv::imwrite(file_path, this->mat());
	if (!success) {
		throw "Error saving file";
	}
}

const cv::Mat& Image::mat() const noexcept
{
	return _mat;
}

cv::Mat& Image::mat() noexcept
{
	return _mat;
}

int Image::width() const noexcept
{
	return _width;
}

int Image::height() const noexcept
{
	return _height;
}

int Image::depth() const noexcept
{
	return _depth;
}

int Image::channels() const noexcept
{
	return _channels;
}
