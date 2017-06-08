#include <FIcon.h>

using namespace cv;

FIcon::FIcon(const cv::Mat &cv_image, float angle, const Rect &frame) {
//  this->cv_image = cut(rotate(cv_image, angle, true), frame);
//  this->q_image = QImage((unsigned char *)cv_image.data, cv_image.cols,
//                         cv_image.rows, cv_image.step, QImage::Format_RGB888)
//                      .rgbSwapped();
}

FIcon::FIcon(const FIcon &icon, float angle, const Rect &frame) {
//  this->cv_image = cut(rotate(icon.to_cv_image(), angle, true), frame);
//  this->q_image = QImage((unsigned char *)cv_image.data, cv_image.cols,
//                         cv_image.rows, cv_image.step, QImage::Format_RGB888)
//                      .rgbSwapped();
}

FIcon::~FIcon() { this->cv_image.release(); }

cv::Mat FIcon::to_cv_image() const { return cv_image; }

QImage FIcon::to_q_image() const { return q_image; }
