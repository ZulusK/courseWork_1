//
// Created by Danil Kazimirov on 05.06.17.
//

#include <FPerson.h>
#include <Facecope.h>
#include <FFaceArea.h>
#include <Utils.h>
#include <iostream>

using namespace std;
using namespace cv;

FPerson::FPerson(FFaceArea &parent, Rect &eye_frame_1, Rect &eye_frame_2, long id) {
    this->parent = &parent;
    set_eyes(eye_frame_1, eye_frame_2);
    set_ID(id);
    this->normilized = false;
}

FPerson::~FPerson() {
    cout << "person deleted" << endl;
}

FFaceArea *FPerson::getParent() {
    return parent;
}

const Eye &FPerson::get_eye_left() {
    return eye_left;
}

const Eye &FPerson::get_eye_rigth() {
    return eye_rigth;
}

long FPerson::get_ID() {
    return ID;
}

void FPerson::set_ID(long id) {
    this->ID = id;
}

Mat FPerson::get_image() {
    normalize();
    Mat p = parent->get_image();
    Mat r = rotate(p, rotation_degree);
    p.release();
    return r(frame);
}

void FPerson::normalize() {
    if (!normilized) {
        //todo
        this->rotation_degree = -toDegrees(getAngle_radians(eye_left.pos, eye_rigth.pos));
        if (rotation_degree > 15) {
            rotation_degree = 15;
        } else if (rotation_degree < -15) {
            rotation_degree = -15;
        }
        normilized = true;
    }
}

bool isValidEye(Rect &eye_frame) {
    return eye_frame.x >= 0 && eye_frame.y >= 0 && eye_frame.height > 0 && eye_frame.width > 0;
}

void FPerson::create_eyes(Rect &eye_frame) {
    Size s = parent->size();
    Eye eye = createEye(eye_frame);

    if (eye.pos.x > s.width / 2) {
        //if it rigth eye
        this->eye_rigth = createEye(eye_frame);
        this->eye_left = getPair(eye_rigth, Rect(0, 0, s.width, s.height));
    } else {
        //if it left eye
        this->eye_left = createEye(eye_frame);
        this->eye_rigth = getPair(eye_rigth, Rect(0, 0, s.width, s.height));
    }
}

void FPerson::set_eyes(cv::Rect &eye_frame_1, cv::Rect &eye_frame_2) {
    bool valid_1 = isValidEye(eye_frame_1);
    bool valid_2 = isValidEye(eye_frame_2);
    if (valid_1 && valid_2) {
        //if two eye is valid
        Size s = parent->size();
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
        Size s = parent->size();
        //if two eye is invalid
        //predict them
        eye_left = Eye{.pos=Point(s.width / 4, s.height / 4), .radius=s.height / 10};
        eye_rigth = Eye{.pos=Point(s.width / 4 * 3, s.height / 4), .radius=s.height / 10};
    }
}