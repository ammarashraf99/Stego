#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

template <typename T>
class Image {
public:
	Image(const std::string& path);
	
	// void save(const std::string& path) const;
	// const std::vector<T>& pixels() const;
	// std::vector<T>& pixels();
	const cv::Mat& mat() const;
	cv::Mat& mat();
	
	int width() const;
	int height() const;
private:
	int _width;
	int _height; 
	cv::Mat _mat;
};
