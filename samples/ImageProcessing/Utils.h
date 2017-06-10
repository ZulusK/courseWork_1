//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_UTILS_H
#define FACECOPE_UTILS_H

#include <string>
#include <Facecope.h>
#include <opencv2/imgproc.hpp>

bool isFileExist(const std::string &path);

cv::Mat toGray(const cv::Mat &src);

Eye createEye(cv::Rect &frame);

Eye getPair(Eye &eye, const cv::Rect &frame);

cv::Point getCenter(const cv::Rect &rect);

cv::Point getCenter(const cv::Mat &M);

float getAngle_radians(const cv::Point &p1, const cv::Point &p2);

float toDegrees(float radians);

float toRadians(float degree);

cv::Size getSize(const cv::Mat &M, float scale);

cv::Size getSize(const cv::Rect &R, float scale);

void rotateRect(cv::Rect &R, const cv::Point2f &center, float angle);

void rotatePoint(int &x, int &y, const cv::Point &center, float angle);

void rotatePoint(cv::Point &point, const cv::Point &center, float angle);

void disableArea(cv::Mat &image, const cv::Rect &rect);

cv::Mat rotate(const cv::Mat &image, float degree, bool increaseBounds = false);

cv::Mat cut(const cv::Mat &original, const cv::Rect &frame);
#endif //FACECOPE_UTILS_H
