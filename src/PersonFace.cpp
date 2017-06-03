//
// Created by Danil Kazimirov on 03.06.17.
//

#include <PersonFace.h>
#include <Utils.h>

using namespace std;
using namespace cv;


PersonFace::PersonFace(const cv::Mat &faceRGB, long id) {
    setId(id);
    setFaceRGB(faceRGB);
}



void PersonFace::setFaceRGB(const Mat &faceRGB) {
    this->faceRGB = faceRGB.clone();
    this->faceGray = toGrayscale(faceRGB);
}

void PersonFace::setFaceGray(const Mat &faceGray) {
    this->faceGray = faceGray;
}

void PersonFace::setEyes(Rect &left, Rect &right) {
    this->eyes[0] = left;
    this->eyes[1] = right;
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
