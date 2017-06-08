#include "FFace.h"
#include <QDebug>
#include <opencv2/imgproc.hpp>

using namespace cv;

void FFace::set_face_frame(const cv::Rect &frame) {
  this->is_normalized = false;
  this->original_frame = frame;
}

void FFace::set_info(const Human &info) {
  this->info.face = info.face;
  this->info.ID = info.ID;
  this->info.sex = info.sex;
}
void FFace::normalize() {
  // todo
  if (!is_normalized) {
    this->rotation = 15;
    //    this->face_frame = rotate(original_frame, center_of_rotation,
    //    rotation);
    this->is_normalized = true;
  }
}

FFace::FFace(int angle, const cv::Rect &face_area_frame, const cv::Rect &eye_1,
             const cv::Rect &eye_2, long ID) {
  this->face_frame = face_area_frame;
  this->original_rotation = angle;
  set_left_eye(eye_1);
  set_rigth_eye(eye_2);
  set_ID(ID);
  is_normalized = false;
}

FFace::~FFace() {}

int FFace::get_rotation() {
  normalize();
  return rotation;
}

int FFace::get_rotation_original() { return original_rotation; }

cv::Rect &FFace::get_face_frame() {
  normalize();
  return face_frame;
}
cv::Rect &FFace::get_original_frame() { return original_frame; }

long FFace::get_ID() { return this->face_area_id; }

Human &FFace::get_info() { return info; }

Eye &FFace::get_left_eye(bool normalized) { return eye_rigth; }

Eye &FFace::get_rigth_eye(bool normalized) { return eye_rigth; }

void FFace::set_original_frame(const cv::Rect &frame) {
  this->original_frame = frame;
  this->is_normalized = false;
}
void FFace::set_ID(long ID) { this->face_area_id = ID; }

void FFace::set_left_eye(const cv::Rect &frame_eye) {
  qDebug() << "set left eye";
  // todo
}

void FFace::set_rigth_eye(const cv::Rect &frame_eye) {
  qDebug() << "set rigth eye";
  // todo;
}

void FFace::set_rotation(int angle) {}
