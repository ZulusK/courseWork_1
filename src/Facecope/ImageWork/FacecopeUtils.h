#ifndef FACECOPEUTILS_H
#define FACECOPEUTILS_H

#include <QImage>
#include <QString>
#include <opencv2/imgproc.hpp>

QImage Mat2QImage(const cv::Mat &cv_image);

cv::Mat QImage2Mat(const QImage &q_image);

bool isImage(const QString &path);

#endif // FACECOPEUTILS_H
