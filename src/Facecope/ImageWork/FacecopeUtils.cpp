#include <FacecopeUtils.h>
#include <QImageReader>
#include <fstream>
#include <opencv2/imgcodecs.hpp>
using namespace cv;
using namespace std;

QImage Mat2QImage(const Mat &cv_image) {
  QImage q_image(cv_image.data, cv_image.cols, cv_image.rows, cv_image.step,
                 QImage::Format_RGB888);
  return q_image.rgbSwapped();
}

Mat QImage2Mat(const QImage &q_image) {
  return Mat(q_image.height(), q_image.width(), CV_8UC3, (void *)q_image.bits(),
             q_image.bytesPerLine());
}

bool isFileExist(const std::string &path) {
  fstream fin(path);
  if (fin.is_open()) {
    fin.close();
    return true;
  } else {
    return false;
  }
}
Mat rotate(const cv::Mat &image, float degree, bool increaseBounds) {
  // get center of image
  Point2f center(image.cols / 2.0, image.rows / 2.0);
  // get rotation matrix
  Mat rot_mat = getRotationMatrix2D(center, degree, 1.0);
  // copy image
  Mat rotated_image;
  if (!increaseBounds) {
    warpAffine(image, rotated_image, rot_mat, image.size());
  } else {
    cv::Rect bbox =
        cv::RotatedRect(center, image.size(), degree).boundingRect();
    warpAffine(image, rotated_image, rot_mat, bbox.size());
  }
  return rotated_image;
}
bool isImage(const QString &path) {
  QImageReader reader(path);
  if (reader.format().size() == 0) {
    return false;
  } else {
    return true;
  }
}

Mat cut(const Mat &original, const Rect &frame) {
  // create mask
  Rect cut_frame;
  cut_frame.x = max(frame.x, 1);
  cut_frame.y = max(frame.y, 1);
  cut_frame.width = min(frame.width + cut_frame.x, original.cols);
  cut_frame.height = min(frame.height + cut_frame.y, original.rows);
  // cut image ange return it
  return original(frame);
}

Mat toGray(const Mat &src) {
  // Create and return grayscaled image:
  if (src.channels() == 3) {
    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);
    return dst;
  } else {
    return src.clone();
  }
}

Point getCenter(const Rect &rect) {
  return Point(rect.x + rect.width / 2, rect.y + rect.height / 2);
}

Point getCenter(const Mat &M) { return Point(M.cols / 2, M.rows / 2); }

float getAngle_radians(const Point &p1, const Point &p2) {
  float angle = 0;
  if (p1.x >= p2.x)
    angle = atan((p1.y - p2.y) / (p1.x - p2.x));
  else
    angle = atan((p2.y - p1.y) / (p2.x - p1.x));
  return angle;
}

float toDegrees(float radians) { return radians / M_PI * 180.0; }

float toRadians(float degree) { return degree * M_PI / 180.0; }

Size getSize(const Mat &M, float scale) {
  return Size(M.cols * scale, M.rows * scale);
}

Size getSize(const Rect &R, float scale) {
  return Size(R.width * scale, R.height * scale);
}

void rotateRect(cv::Rect &R, const cv::Point2f &center, float angle) {
  int xC = R.x + R.width / 2;
  int yC = R.y + R.height / 2;
  // rotate center of rect
  rotatePoint(xC, yC, center, angle);
  R.x = xC - R.width / 2;
  R.y = yC - R.height / 2;
}

void rotatePoint(int &x, int &y, const cv::Point &center, float angle) {
  float ca = cosf(angle);
  float sa = sinf(angle);
  // copy val
  float dx = x - center.x;
  float dy = y - center.y;
  // move to new CS
  x = ca * dx - sa * dy + center.x;
  y = sa * dx + ca * dy + center.y;
}

void rotatePoint(Point &point, const cv::Point &center, float angle) {
  rotatePoint(point.x, point.y, center, angle);
}

void disableArea(Mat &image, const Rect &rect) {
  int radius = cvRound((rect.width + rect.height) * 0.4);
  circle(image, getCenter(rect), radius, Scalar(0, 0, 0), -1, 8, 0);
}

Eye createEye(cv::Rect &frame) {
  return Eye{.pos =
                 Point(frame.x + frame.width / 2, frame.y + frame.height / 2),
             .radius = cvRound((frame.width + frame.height) * 0.25)};
}

Eye getPair(Eye &eye, const Rect &frame) {
  return Eye{.pos = Point(frame.width - eye.pos.x, eye.pos.y),
             .radius = eye.radius};
}

