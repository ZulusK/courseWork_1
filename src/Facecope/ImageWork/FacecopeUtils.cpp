#include <FacecopeUtils.h>
#include <QImageReader>
#include <opencv2/imgcodecs.hpp>
using namespace cv;

QImage Mat2QImage(const Mat &cv_image) {
  QImage q_image(cv_image.data, cv_image.cols, cv_image.rows, cv_image.step,
                 QImage::Format_RGB888);
  return q_image.rgbSwapped();
}

Mat QImage2Mat(const QImage &q_image) {
  return Mat(q_image.height(), q_image.width(), CV_8UC3, (void *)q_image.bits(),
             q_image.bytesPerLine());
}

bool isImage(const QString &path) {
  QImageReader reader(path);
  if (reader.format().size() == 0) {
    return false;
  } else {
    return true;
  }
}
