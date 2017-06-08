#include "FImage.h"
#include <FacecopeUtils.h>
#include <QImage>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

FImage::FImage(const Mat &mat) {
  this->name = "";
  this->cv_image = mat.clone();
  this->is_detected = false;
  this->is_recognized = false;
  this->q_image = Mat2QImage(cv_image);
}

FImage::FImage(const QString &path) {
  if (isImage(path)) {
    // load qimage, its faster
    this->q_image = QImage(path);
    this->cv_image = QImage2Mat(q_image);
    this->name = path;
  }
  this->is_detected = false;
  this->is_recognized = false;
}

FImage::~FImage() { this->cv_image.release(); }

QString FImage::get_name() const { return name; }

QImage FImage::to_q_image() { return q_image; }

void FImage::set_recognized(bool recognized) {
  this->is_recognized = recognized;
}

void FImage::set_detected(bool detected) { this->is_detected = detected; }

void FImage::clear() {
  // todo
}

bool FImage::empty() const { return q_image.isNull() || cv_image.empty(); }

Size FImage::cv_size() const { return Size(cv_image.cols, cv_image.rows); }
QSize FImage::q_size() const { return q_image.size(); }
