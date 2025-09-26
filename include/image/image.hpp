#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class Image {
public:
	Image(const std::string& path);
	
	void save(const std::string& path) const;

	const cv::Mat& mat() const noexcept;
	cv::Mat& mat() noexcept;
	int width() const noexcept;
	int height() const noexcept;
	int depth() const noexcept;
	int channels() const noexcept;
private:
	cv::Mat _mat;
	int _width;
	int _height; 
	int _depth;
	int _channels;
};
