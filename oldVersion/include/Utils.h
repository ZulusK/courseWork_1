//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FACECOPE_UTILS_H
#define FACECOPE_UTILS_H

#include <opencv2/imgproc.hpp>
#include <string>

cv::Mat toGrayscale(const cv::Mat &src);

bool isValidPath(const std::string &path);

cv::Point2f getCenter(const cv::Rect &rect);

float getRotation_radians(const cv::Rect &rect1, const cv::Rect &rect2);

cv::Size getSize(const cv::Mat &M, float scale);

cv::Size getSize(const cv::Rect &R, float scale);

void rotateRect(cv::Rect &R, const cv::Point2f &center, float angle);

void rotatePoint(float &x, float &y, const cv::Point2f &center, float angle);

void rotatePoint(int &x, int &y, const cv::Point2f &center, float angle);

float toRadians(float degree);

float toDegrees(float radians);

cv::Rect copyEye(const cv::Rect &eye, const cv::Rect &frame);

void disableArea(cv::Mat &image, const cv::Rect &rect);

#endif //FISHERFACE_UTILS_H
