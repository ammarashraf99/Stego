#include "image.hpp"
#include <opencv2/core/matx.hpp>

template <typename T>
Image<T>::Image(const std::string& path)
{
	_mat = cv::imread(path);

	if (_mat.empty())
		throw "error loading mat\n";

	_width = _mat.cols;
	_height = _mat.rows;
}


template <typename T>
const cv::Mat& Image<T>::mat() const
{
	return _mat;
}

template <typename T>
cv::Mat& Image<T>::mat()
{
	return _mat;
}


template <typename T>
int Image<T>::width() const
{
	return _width;
}


template <typename T>
int Image<T>::height() const
{
	return _height;
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


