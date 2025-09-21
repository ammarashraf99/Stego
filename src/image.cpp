#include "image.hpp"
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgcodecs.hpp>

Image::Image(const std::string& path)
{
	_mat = cv::imread(path);

	if (_mat.empty())
		throw "error loading mat\n";

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


const cv::Mat& Image::mat() const
{
	return _mat;
}

cv::Mat& Image::mat()
{
	return _mat;
}

int Image::width() const
{
	return _width;
}

int Image::height() const
{
	return _height;
}

int Image::depth() const 
{
	return _depth;
}

int Image::channels() const 
{
	return _channels;
}

// template <typename T>
// const std::vector<T>& Image<T>::pixels() const
// {
// 	return _pixels;
// }

// template <typename T>
// std::vector<T>& Image<T>::pixels() 
// {
// 	return _pixels;
// }



	// std::pair<int, int> dep_chann_tmp;
	// dep_chann_tmp = [](int en) -> std::pair<int, int> {
	// 	switch (en) {
	// 	case CV_8SC1:
	// 	case CV_8UC1:
	// 	return {8, 1};

	// 	case CV_8SC2:
	// 	case CV_8UC2:
	// 	return {8, 2};

	// 	case CV_8SC3:
	// 	case CV_8UC3:
	// 	return {8, 3};

	// 	case CV_8SC4:
	// 	case CV_8UC4:
	// 	return {8, 4};

	// 	default:
	// 	return {-1, -1};
	// 	}
	// }(_mat.depth());
