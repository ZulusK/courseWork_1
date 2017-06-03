//
// Created by Danil Kazimirov on 02.06.17.
//

#include <FaceDetector.h>
#include <string>
#include <fstream>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <Utils.h>

using namespace std;
using namespace cv;

enum {
    FACE = 0xA,
    EYE,
    SMILE
};


FaceDetector::FaceDetector(const string &cascadeFolderPath) {
    CascadeClassifier *face_cascade;
    CascadeClassifier *eyes_cascade;
    CascadeClassifier *smile_cascade;

    //load face cascade from file
    if (isValidPath(cascadeFolderPath + FACE_CASCADE_NAME)) {
        face_cascade = new CascadeClassifier();
        face_cascade->load(cascadeFolderPath + FACE_CASCADE_NAME);
        cascades[FACE] = face_cascade;
    }

    //load eye cascade from file
    if (isValidPath(cascadeFolderPath + EYE_CASCADE_NAME)) {
        eyes_cascade = new CascadeClassifier();
        eyes_cascade->load(cascadeFolderPath + EYE_CASCADE_NAME);
        cascades[EYE] = eyes_cascade;
    }

    //load smile cascade from file
    if (isValidPath(cascadeFolderPath + SMILE_CASCADE_NAME)) {
        smile_cascade = new CascadeClassifier();
        smile_cascade->load(cascadeFolderPath + SMILE_CASCADE_NAME);
        cascades[SMILE] = smile_cascade;
    }


    this->default_scale = 1.5;
}

FaceDetector::~FaceDetector() {
    for (auto it = cascades.begin(); it != cascades.end(); it++) {
        delete it->second;
    }
    cascades.clear();
}


Mat FaceDetector::normalizeFace(cv::Mat &image) {
    vector<Rect> eyes;
    Mat gray = toGrayscale(image);
    //find eyes
    if (cascades.find(EYE) != cascades.end()) {
        findObject(*cascades[EYE], gray, eyes, default_scale, default_min_size, default_min_size);
    }
    Mat dst;

    if (eyes.size() > 2) {
        float angle = getRotation(eyes[0], eyes[1]);
        Mat rot_mat = getRotationMatrix2D(Point2f(image.cols / 2.0, image.rows / 2.0), angle, 1.0);
        warpAffine(image, dst, rot_mat, image.size());
    } else {
        dst = image.clone();
    }
    return dst;
}

Mat FaceDetector::getFace(const Mat &image, const Rect &rect, bool normalized) {
    Mat cropped = image(rect);
    if (!normalized) {
        return cropped;
    } else {
        return normalizeFace(cropped);
    }
}

void FaceDetector::getFaces(const Mat &image, vector<Mat> &faces, bool toGray, bool normalized) {
    vector<Rect> rects;
    Mat gray = toGrayscale(image);
    detectFaces(gray, rects, true);
    if (toGray) {
        getFaces(gray, rects, faces, true, normalized);
    } else {
        getFaces(image, rects, faces, false, normalized);
    }
}

void FaceDetector::getFaces(const Mat &image, vector<Rect> &rects, vector<Mat> &faces, bool toGray, bool normalized) {
    if (toGray) {
        auto gray = toGrayscale(image);
        for (auto it = rects.begin(); it != rects.end(); it++) {
            faces.push_back(getFace(gray, *it, normalized));
        }
    } else {
        for (auto it = rects.begin(); it != rects.end(); it++) {
            faces.push_back(getFace(image, *it, normalized));
        }
    }
}

bool FaceDetector::isLoaded_face() {
    return cascades.find(FACE) != cascades.end() && !cascades[FACE]->empty();
}

bool FaceDetector::isLoaded_eye() {
    return cascades.find(EYE) != cascades.end() && !cascades[EYE]->empty();
}

bool FaceDetector::isLoaded_smile() {
    return cascades.find(SMILE) != cascades.end() && !cascades[SMILE]->empty();
}

void FaceDetector::findObject(CascadeClassifier &classifier, const cv::Mat &grayImage, std::vector<cv::Rect> &rects,
                              double scaleFactor,
                              cv::Size minSize, cv::Size maxSize) {
    if (!classifier.empty() || grayImage.channels() > 1) {
        classifier.detectMultiScale(grayImage, rects, scaleFactor, 3, 0 | CASCADE_SCALE_IMAGE, minSize, maxSize);
    }
}

void FaceDetector::detectEyes(const cv::Mat &image, std::vector<cv::Rect> &rects, double scaleFactor, cv::Size minSize,
                              cv::Size maxSize) {
    if (isLoaded_eye()) {
        auto gray = toGrayscale(image);
        findObject(*cascades[EYE], gray, rects, scaleFactor, minSize, maxSize);
    }
}


void
FaceDetector::detectFaces(const Mat &image, vector<Rect> &rects, bool removeArtifacts, double scaleFactor, Size minSize,
                          Size maxSize) {
    if (isLoaded_face()) {
        auto gray = toGrayscale(image);
        findObject(*cascades[FACE], gray, rects, scaleFactor, minSize, maxSize);
        if (removeArtifacts && isLoaded_eye()) {
            for (int i = 0; i < rects.size(); i++) {
                vector<Rect> eyes;
                findObject(*cascades[EYE], gray(rects[i]), eyes, default_scale, default_min_size, default_max_size);
                if (eyes.empty()) {
                    rects.erase(rects.begin() + i);
                    i--;
                }
            }
        }
    }
}

void FaceDetector::detectSmile(const cv::Mat &image, std::vector<cv::Rect> &rects, double scaleFactor, cv::Size minSize,
                               cv::Size maxSize) {
    if (isLoaded_smile()) {
        auto gray = toGrayscale(image);
        findObject(*cascades[SMILE], gray, rects, scaleFactor, minSize, maxSize);
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

void FaceDetector::getFaces(const cv::Mat &image, std::vector<cv::Rect> &rects, std::vector<PersonFace *> &persons,
                            bool normalized) {
    Mat gray = toGrayscale(image);
    detectFaces(image, rects, false,default_scale,default_min_size,default_max_size);

}

float FaceDetector::getDef_faceScale_min() const {
    return def_faceScale_min;
}

void FaceDetector::setDef_faceScale_min(float def_faceScale_min) {
    FaceDetector::def_faceScale_min = def_faceScale_min;
}

float FaceDetector::getDef_eyeScale_min() const {
    return def_eyeScale_min;
}

void FaceDetector::setDef_eyeScale_min(float def_eyeScale_min) {
    FaceDetector::def_eyeScale_min = def_eyeScale_min;
}

float FaceDetector::getDef_mouthScale_min() const {
    return def_mouthScale_min;
}

void FaceDetector::setDef_mouthScale_min(float def_mouthScale_min) {
    FaceDetector::def_mouthScale_min = def_mouthScale_min;
}

float FaceDetector::getDef_faceScale_max() const {
    return def_faceScale_max;
}

void FaceDetector::setDef_faceScale_max(float def_faceScale_max) {
    FaceDetector::def_faceScale_max = def_faceScale_max;
}

float FaceDetector::getDef_eyeScale_max() const {
    return def_eyeScale_max;
}

void FaceDetector::setDef_eyeScale_max(float def_eyeScale_max) {
    FaceDetector::def_eyeScale_max = def_eyeScale_max;
}

float FaceDetector::getDef_mouthScale_max() const {
    return def_mouthScale_max;
}

void FaceDetector::setDef_mouthScale_max(float def_mouthScale_max) {
    FaceDetector::def_mouthScale_max = def_mouthScale_max;
}

double FaceDetector::getDef_scaleFactor() const {
    return def_scaleFactor;
}

void FaceDetector::setDef_scaleFactor(double def_scaleFactor) {
    FaceDetector::def_scaleFactor = def_scaleFactor;
}
