#ifndef FACECOPEUTILS_H
#define FACECOPEUTILS_H

#include <FacecopeTypes.h>
#include <QImage>
#include <QString>
#include <opencv2/imgproc.hpp>

QImage Mat2QImage(const cv::Mat &cv_image);

cv::Mat QImage2Mat(const QImage &q_image);

bool isImage(const QString &path);

cv::Mat toGray(const cv::Mat &src);

cv::Mat cut(const cv::Mat &original, const cv::Rect &frame);

Eye createEye(const cv::Rect &frame);

Eye getPair(Eye &eye, const cv::Rect &frame);

cv::Point getCenter(const cv::Rect &rect);

cv::Point getCenter(const cv::Mat &M);

bool isFileExist(const std::string &path);

float getAngle_radians(const cv::Point &p1, const cv::Point &p2);

float toDegrees(float radians);

float toRadians(float degree);

cv::Size getSize(const cv::Mat &M, float scale);

cv::Size getSize(const cv::Rect &R, float scale);

void rotateRect(cv::Rect &R, const cv::Point2f &center, float angle);


void rotatePoint(int &x, int &y, const cv::Point &center, float angle);

void rotatePoint(cv::Point &point, const cv::Point &center, float angle);

cv::Mat rotate(const cv::Mat &image, float degree, bool increaseBounds = false);

void disableArea(cv::Mat &image, const cv::Rect &rect);
#endif // FACECOPEUTILS_H
