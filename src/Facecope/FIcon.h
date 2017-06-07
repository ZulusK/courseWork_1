#ifndef ICON_H
#define ICON_H
#include <QImage>
#include <opencv2/imgproc.hpp>

class FIcon {
  cv::Mat cv_image;
  QImage q_image;

public:
  FIcon(const cv::Mat &cv_image, float angle,
        const cv::Rect &frame = cv::Rect());
  FIcon(const FIcon &icon, float angle, const cv::Rect &frame = cv::Rect());

  ~FIcon();
  cv::Mat to_cv_image() const;
  QImage to_q_image() const;
};

#endif // ICON_H
