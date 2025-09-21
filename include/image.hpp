#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

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
	int depth() const;
	int channels() const;
private:
	cv::Mat _mat;
	int _width;
	int _height; 
	// std::pair<int, int> _depth_channel;
	int _depth;
	int _channels;
};
