//
// Created by Danil Kazimirov on 02.06.17.
//

#include <FaceDetector.h>
#include <string>
#include <fstream>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

bool isValidPath(const string &path) {
    fstream fin(path);
    if (fin.is_open()) {
        fin.close();
        return true;
    } else {
        return false;
    }
}

Mat toGrayscale(const Mat &src) {
    // Create and return grayscaled image:
    Mat dst;
    switch (src.channels()) {
        case 3:
            cvtColor(src, dst, COLOR_BGR2GRAY);
            break;
        default:
            dst = src;
            break;
    }
    return dst;
}

FaceDetector::FaceDetector(const string &cascadeFolderPath) {
    //load cascade from file
    if (isValidPath(cascadeFolderPath + FACE_CASCADE_NAME)) {
        face_cascade.load(cascadeFolderPath + FACE_CASCADE_NAME);
    } else if (isValidPath(cascadeFolderPath + "/" + FACE_CASCADE_NAME)) {
        face_cascade.load(cascadeFolderPath + "/" + FACE_CASCADE_NAME);
    }
    this->default_scale = 1.5;
}

FaceDetector::~FaceDetector() {

}

void FaceDetector::detectFaces(const Mat &image, vector<Rect> &rects, double scaleFactor, Size minSize, Size maxSize) {
    if (!face_cascade.empty()) {
        auto gray = toGrayscale(image);
        face_cascade.detectMultiScale(gray, rects, scaleFactor, 3, 0 | CASCADE_SCALE_IMAGE, minSize, maxSize);
    }
}

Mat FaceDetector::getFace(const Mat &image, const Rect &rect) {
    return image(rect);
}

void FaceDetector::getFaces(const Mat &image, vector<Mat> &faces, bool toGray) {
    vector<Rect> rects;
    Mat gray = toGrayscale(image);
    detectFaces(gray, rects);
    if (toGray) {
        getFaces(gray, rects, faces, true);
    } else {
        getFaces(image, rects, faces, false);
    }
}

void FaceDetector::getFaces(const Mat &image, vector<Rect> &rects, vector<Mat> &faces, bool toGray) {
    if (toGray) {
        auto gray = toGrayscale(image);
        for (auto it = rects.begin(); it != rects.end(); it++) {
            faces.push_back(getFace(gray, *it));
        }
    } else {
        for (auto it = rects.begin(); it != rects.end(); it++) {
            faces.push_back(getFace(image, *it));
        }
    }
}

const Size &FaceDetector::getDefault_min_size() const {
    return default_min_size;
}

void FaceDetector::setDefault_min_size(const Size &default_min_size) {
    this->default_min_size = default_min_size;
}

const Size &FaceDetector::getDefault_max_size() const {
    return default_max_size;
}

void FaceDetector::setDefault_max_size(const Size &default_max_size) {
    this->default_max_size = default_max_size;
}

double FaceDetector::getDefault_scale() const {
    return default_scale;
}

void FaceDetector::setDefault_scale(double default_scale) {
    if (default_scale > 1)
        this->default_scale = default_scale;
}

bool FaceDetector::isLoaded() {
    return !face_cascade.empty();
}