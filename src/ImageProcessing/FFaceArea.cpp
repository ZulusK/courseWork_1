//
// Created by Danil Kazimirov on 05.06.17.
//

#include <FFaceArea.h>
#include <FImage.h>

using namespace std;
using namespace cv;

FFaceArea::FFaceArea(const cv::Rect &frame, cv::Rect &eye_1, cv::Rect &eye_2, FImage *parent) {
    this->parent = parent;
    set_frame(frame);
    this->ID = -1;
    this->person = new FPerson(*this, eye_1, eye_2);
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

cv::Mat FFaceArea::get_image() {
    if (parent) {
        const Mat original = parent->get_image();
        return original(frame);
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