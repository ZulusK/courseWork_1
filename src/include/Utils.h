//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_UTILS_H
#define FISHERFACE_UTILS_H

#include <opencv2/imgproc.hpp>
#include <string>

cv::Mat toGrayscale(const cv::Mat &src);

bool isValidPath(const std::string &path);

cv::Point2f getCenter(const cv::Rect &rect);

float getRotation(const cv::Rect &rect1, const cv::Rect &rect2);

#endif //FISHERFACE_UTILS_H