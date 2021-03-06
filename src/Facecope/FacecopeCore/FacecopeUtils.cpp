#include "opencv2/core/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <FDatabaseDriver.h>
#include <FFace.h>
#include <FFaceDetector.h>
#include <FFaceRecognizer.h>
#include <FacecopeUtils.h>
#include <QDebug>
#include <QImageReader>
#include <fstream>
#include <vector>
using namespace cv;
using namespace std;

QImage Mat2QImage(const Mat &cv_image) {
  switch (cv_image.type()) {
  // 8-bit, 4 channel
  case CV_8UC4: {
    QImage image(cv_image.data, cv_image.cols, cv_image.rows,
                 static_cast<int>(cv_image.step), QImage::Format_ARGB32);

    return image;
  }

  // 8-bit, 3 channel
  case CV_8UC3: {
    QImage image(cv_image.data, cv_image.cols, cv_image.rows,
                 static_cast<int>(cv_image.step), QImage::Format_RGB888);

    return image.rgbSwapped();
  }

  // 8-bit, 1 channel
  case CV_8UC1: {
    QImage image(cv_image.data, cv_image.cols, cv_image.rows,
                 static_cast<int>(cv_image.step), QImage::Format_Grayscale8);
    return image;
  }
  }

  return QImage();
}

Mat QImage2Mat(const QImage &inImage) {
  switch (inImage.format()) {
  // 8-bit, 4 channel
  case QImage::Format_ARGB32:
  case QImage::Format_ARGB32_Premultiplied: {
    cv::Mat mat(inImage.height(), inImage.width(), CV_8UC4,
                const_cast<uchar *>(inImage.bits()),
                static_cast<size_t>(inImage.bytesPerLine()));

    return mat.clone();
  }

  // 8-bit, 3 channel
  case QImage::Format_RGB32:
  case QImage::Format_RGB888: {
    QImage swapped = inImage;

    if (inImage.format() == QImage::Format_RGB32) {
      swapped = swapped.convertToFormat(QImage::Format_RGB888);
    }

    swapped = swapped.rgbSwapped();

    return cv::Mat(swapped.height(), swapped.width(), CV_8UC3,
                   const_cast<uchar *>(swapped.bits()),
                   static_cast<size_t>(swapped.bytesPerLine()))
        .clone();
  }

  // 8-bit, 1 channel
  case QImage::Format_Indexed8: {
    cv::Mat mat(inImage.height(), inImage.width(), CV_8UC1,
                const_cast<uchar *>(inImage.bits()),
                static_cast<size_t>(inImage.bytesPerLine()));

    return mat.clone();
  }
  }
  return cv::Mat();
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
  cut_frame.x = max(frame.x, 0);
  cut_frame.y = max(frame.y, 0);
  cut_frame.width = max(min(frame.width, original.cols - cut_frame.x), 1);
  cut_frame.height = max(min(frame.height, original.rows - cut_frame.y), 1);
  // cut image ange return it
  return original(cut_frame);
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
    angle = atan((p1.y - p2.y) / (p1.x - p2.x + 0.00000000001));
  else
    angle = atan((p2.y - p1.y) / (p2.x - p1.x + 0.00000000001));
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

Eye createEye(const cv::Rect &frame) {
  return Eye{.pos =
                 Point(frame.x + frame.width / 2, frame.y + frame.height / 2),
             .radius = cvRound((frame.width + frame.height) * 0.25)};
}

Eye getPair(Eye &eye, const Rect &frame) {
  return Eye{.pos = Point(frame.width - eye.pos.x, eye.pos.y),
             .radius = eye.radius};
}

void learnNewHuman(Facecope &facecope, int id, int gender) {
  int deviceId = 0;
  // Get a handle to the Video device:
  VideoCapture cap(deviceId);
  // Check if we can use this device at all:
  if (!cap.isOpened()) {
    return;
  }
  // Holds the current frame from the Video device:
  Mat frame;
  vector<Mat> images;
  vector<Mat> images_gender;
  vector<int> ids;
  vector<int> genders;
  for (int i = 0; i < 100; i++) {
    cap >> frame;
    // Find the faces in the frame:
    vector<FFace *> faces;
    facecope.detector->detect_faces(frame, faces, true, LBP);
    Mat original = frame.clone();
    if (!faces.empty()) {
      // get first frame
      Rect face_frame = faces[0]->get_original_frame();
      ids.push_back(id);

      // cropp face
      Mat face = frame(face_frame);
      images.push_back(face);
      int prediction = facecope.recognizer_gender->recognize(face);
      string box_text = "";
      if (prediction == 1) {
        box_text = "man";
      } else if (prediction == 2) {
        box_text = "woman";
      } else {
        box_text = "not recognized";
      }
      // if ot recogize gender
      if (prediction != gender) {
        images_gender.push_back(face);
        genders.push_back(gender);
      }
      rectangle(original, face_frame, CV_RGB(0, 255, 0), 1);
      int pos_x = std::max(face_frame.tl().x - 10, 0);
      int pos_y = std::max(face_frame.tl().y - 10, 0);
      putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0,
              CV_RGB(0, 255, 0), 2.0);
      for (int i = 0; i < faces.size(); i++) {
        delete faces[i];
      }
    }
    imshow("Facecop (press ESC to break)", original);
    char key = (char)waitKey(20);
    if (key == 27)
      break;
  }
  if (ids.size() > 2) {
    ids.pop_back();
    ids.push_back(-1);
    facecope.recognizer_face->learn(images, ids);
  }
  if (genders.size() > 2) {
    genders.pop_back();
    genders.push_back(-1);
    facecope.recognizer_gender->learn(images_gender, genders);
  }
}
