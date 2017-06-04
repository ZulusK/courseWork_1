//
// Created by Danil Kazimirov on 03.06.17.
//

#include <PersonFace.h>
#include <Utils.h>

using namespace std;
using namespace cv;


PersonFace::PersonFace(const cv::Mat &faceRGB, const cv::Mat &faceGray, long id) {
    setId(id);
    this->faceRGB = faceRGB.clone();
    this->faceGray = faceGray.clone();
    if (this->faceRGB.empty()) {
        this->faceRGB = Mat::zeros(1, 1, CV_8UC3);
    }
    if (this->faceGray.empty()) {
        this->faceGray = Mat::zeros(1, 1, CV_8UC1);
    }

}

PersonFace::PersonFace(const cv::Mat &faceRGB, long id) {
    setId(id);
    this->faceRGB = faceRGB.clone();
    if (this->faceRGB.empty()) {
        this->faceRGB = Mat::zeros(1, 1, CV_8UC3);
    }
    this->faceGray = toGrayscale(this->faceRGB);
}

void PersonFace::setEyes(Rect &left, Rect &right) {
    if (left.x > right.x) {
        this->eyes[1] = left;
        this->eyes[0] = right;
    } else {
        this->eyes[0] = left;
        this->eyes[1] = right;
    }
}

void PersonFace::setSmile(const Rect &smile) {
    this->smile = smile;
}

const Mat &PersonFace::getFaceRGB() const {
    return faceRGB;
}

const Mat &PersonFace::getFaceGray() const {
    return faceGray;
}

const Rect *PersonFace::getEyes() const {
    return eyes;
}

const Rect &PersonFace::getSmile() const {
    return smile;
}

void PersonFace::setId(long id) {
    this->id = id;
}

PersonFace::~PersonFace() {

}

void PersonFace::setFaceRGB(const Mat &faceRGB) {
    this->faceRGB = faceRGB;
    if (this->faceRGB.empty()) {
        this->faceRGB = Mat::zeros(1, 1, CV_8UC3);
    }
    this->faceGray = toGrayscale(this->faceRGB);
}
