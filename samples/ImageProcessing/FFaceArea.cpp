//
// Created by Danil Kazimirov on 05.06.17.
//

#include <FFaceArea.h>
#include <FImage.h>
#include <Utils.h>

using namespace std;
using namespace cv;

FFaceArea::FFaceArea(const cv::Rect &frame, cv::Rect &eye_1, cv::Rect &eye_2, FImage *parent, int angle,
                     const Point &centerOfRotation) {
    this->parent = parent;
    this->angle = angle;
    set_frame(frame);
    rotated_frame = Rect(frame);
    this->centerOfRotation = centerOfRotation;
    this->ID = -1;
    this->person = new FPerson(*this, eye_1, eye_2);
    this->normalized = false;
}

void FFaceArea::set_frame(const Rect &frame) {
    this->frame = frame;
    if (this->frame.x <= 0) {
        this->frame.x = 1;
    }
    if (this->frame.y <= 0) {
        this->frame.y = 1;
    }
}

FFaceArea::~FFaceArea() {
    delete this->person;
}

cv::Size FFaceArea::size() {
    return frame.size();
}

void FFaceArea::set_parent(FImage &parent) {
    this->parent = &parent;
}

FPerson *FFaceArea::get_person() {
    return person;
}

long FFaceArea::get_areaID() {
    return this->ID;
}

void FFaceArea::set_areaID(long id) {
    this->ID = id;
}


void FFaceArea::normalize() {
    if (!normalized && parent) {
        rotateRect(rotated_frame, centerOfRotation, -toRadians(angle));
        normalized = true;
    }
}

cv::Mat FFaceArea::get_image() {
    if (parent) {
        if (angle == 0) {
            const Mat original = parent->get_image();
            return original(frame);
        } else {
            normalize();
            Mat r = rotate(parent->get_image(), angle, true);
            return r(rotated_frame);
        }
    } else {
        return Mat::zeros(1, 1, CV_8UC1);
    }
}

FImage *FFaceArea::get_parent() {
    return parent;
}

const cv::Rect FFaceArea::get_frame() {
    return this->frame;
}

int FFaceArea::get_angle() const {
    return angle;
}
