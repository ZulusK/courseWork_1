#include "FImage.h"
#include <FacecopeUtils.h>
#include <QDebug>
#include <QImage>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

Mat FImage::get_face_cv_image(FFace *face) {
  auto rotated = rotate(cv_image, face->get_rotation_original(), true);
  auto face_area = cut(rotated, face->get_original_frame());
  auto face_image =
      cut(rotate(face_area, face->get_rotation()), face->get_face_frame());
  return face_image;
}

QRect FImage::get_face_q_frame(FFace *face) {
  Rect original = face->get_original_frame();
  // clone
  Rect rotated(original.x, original.y, original.width, original.height);
  // rotate
  rotateRect(rotated, getCenter(cv_image),
             toRadians(face->get_rotation_original()));
  // cut
  return QRect(rotated.x, rotated.y, rotated.width, rotated.height);
}

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
    if (q_image.format() == QImage::Format_Indexed8) {
      q_image = q_image.convertToFormat(QImage::Format_RGB888);
    }
    this->cv_image = QImage2Mat(q_image);
    this->name = path;
  }
  this->is_detected = false;
  this->is_recognized = false;
}

int FImage::add_face(FFace *face) {
  this->faces.append(face);
  face->set_ID(faces.size() - 1);
  qDebug() << "face aded " << face->get_ID();
  return face->get_ID();
}

void FImage::add_faces(std::vector<FFace *> &faces) {
  for (auto it = faces.begin(); it != faces.end(); it++) {
    add_face(*it);
  }
}

FImage::~FImage() { this->cv_image.release(); }

QString FImage::get_name() const { return name; }

QImage FImage::to_q_image() { return q_image; }

Mat FImage::to_cv_image() { return cv_image; }

void FImage::set_recognized(bool recognized) {
  this->is_recognized = recognized;
}

void FImage::set_detected(bool detected) { this->is_detected = detected; }

void FImage::clear() {
  // todo
}

bool FImage::empty() const { return q_image.isNull() || cv_image.empty(); }

Size FImage::cv_size() const { return Size(cv_image.cols, cv_image.rows); }
QSize FImage::q_size() const { return QSize(cv_image.cols, cv_image.rows); }

FFace *FImage::remove_face(long ID) {
  if (this->faces.size() >= ID || ID < 0) {
    return NULL;
  } else {
    auto face = faces.at(ID);
    faces[ID] = faces[faces.size() - 1];
    faces[ID]->set_ID(ID);
    faces.remove(faces.size() - 1);
    return face;
  }
}

QVector<FFace *> &FImage::get_faces() { return faces; }

FFace *FImage::get_face(long ID) {
  if (ID >= faces.size() || ID < 0) {
    return NULL;
  } else {
    return faces.at(ID);
  }
}
