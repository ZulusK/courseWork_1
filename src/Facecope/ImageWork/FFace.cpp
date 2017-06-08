#include "FFace.h"
#include <FacecopeUtils.h>
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
    // todo
    this->rotation = toDegrees(getAngle_radians(eye_left.pos, eye_rigth.pos));
    if (rotation > 15) {
      rotation = 15;
    } else if (rotation < -15) {
      rotation = -15;
    }
    // randomize rotation to debug
    //    rotation = 20;
    qDebug() << "rotation " << rotation;
    this->is_normalized = true;
    auto _e1 = eye_left;
    auto _e2 = eye_rigth;
    this->face_frame.x = max(_e1.pos.x - _e1.radius * 2, 0);
    this->face_frame.y =
        max(min(_e1.pos.y - _e1.radius * 2, _e2.pos.y - _e2.radius * 2), 0);
    this->face_frame.width = min(_e2.pos.x + _e2.radius * 2 - face_frame.x,
                                 original_frame.width - face_frame.x);
    this->face_frame.height = original_frame.height - face_frame.y;
  }
}

FFace::FFace(int angle_src, const cv::Rect &frame_src, const cv::Rect &eye_1,
             const cv::Rect &eye_2, long ID) {
  this->original_frame = frame_src;
  this->face_frame = Rect(0, 0, original_frame.width, original_frame.height);
  this->original_rotation = angle_src;
  qDebug() << angle_src << " original rotation";
  this->rotation = 15;
  set_eyes(eye_1, eye_2);
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

bool isValidEye(const Rect &eye_frame) {
  return eye_frame.x >= 0 && eye_frame.y >= 0 && eye_frame.height > 0 &&
         eye_frame.width > 0;
}

void FFace::set_rotation(int angle) { this->original_rotation = angle; }

void FFace::create_eyes(const Rect &eye_frame) {
  Size s = original_frame.size();
  Eye eye = createEye(eye_frame);

  if (eye.pos.x > s.width >> 1) {
    // if it rigth eye
    this->eye_rigth = eye;
    this->eye_left = getPair(eye, Rect(0, 0, s.width, s.height));
  } else {
    // if it left eye
    this->eye_left = eye;
    this->eye_rigth = getPair(eye, Rect(0, 0, s.width, s.height));
  }
}

void FFace::set_eyes(const cv::Rect &eye_frame_1, const cv::Rect &eye_frame_2) {
  bool valid_1 = isValidEye(eye_frame_1);
  bool valid_2 = isValidEye(eye_frame_2);
  Size s = original_frame.size();
  if (valid_1 && valid_2) {
    // if two eye is valid
    Eye eye = createEye(eye_frame_1);
    if (eye.pos.x < s.width / 2) {
      eye_left = eye;
      eye_rigth = createEye(eye_frame_2);
    } else {
      eye_rigth = eye;
      eye_left = createEye(eye_frame_2);
    }
  } else if (valid_1) {
    create_eyes(eye_frame_1);
  } else if (valid_2) {
    create_eyes(eye_frame_2);
  } else {
    // if two eye is invalid
    // predict them
    eye_left =
        Eye{.pos = Point(s.width / 4, s.height / 3), .radius = s.height / 6};
    eye_rigth = Eye{.pos = Point(s.width / 4 * 3, s.height / 3),
                    .radius = s.height / 6};
  }
  if (eye_rigth.radius < 3) {
    eye_rigth.radius = 3;
  }
  if (eye_left.radius < 3) {
    eye_left.radius = 3;
  }
  is_normalized = false;
}
