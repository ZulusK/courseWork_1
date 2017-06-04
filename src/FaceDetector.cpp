//
// Created by Danil Kazimirov on 03.06.17.
//

#include <FaceDetector.h>
#include <Utils.h>
#include <iostream>

using namespace std;
using namespace cv;
enum {
    FACE = 0xA,
    EYE,
    SMILE
};

FaceDetector::FaceDetector(const std::string &cascadeFolderPath) {
    if (isValidPath(cascadeFolderPath + FACE_CASCADE_NAME)) {
        cascades[FACE] = new CascadeClassifier();
        cascades[FACE]->load(cascadeFolderPath + FACE_CASCADE_NAME);
    }
    if (isValidPath(cascadeFolderPath + EYE_CASCADE_NAME)) {
        cascades[EYE] = new CascadeClassifier();
        cascades[EYE]->load(cascadeFolderPath + EYE_CASCADE_NAME);
    }
    if (isValidPath(cascadeFolderPath + SMILE_CASCADE_NAME)) {
        cascades[SMILE] = new CascadeClassifier();
        cascades[SMILE]->load(cascadeFolderPath + SMILE_CASCADE_NAME);
    }
    this->def_scaleFactor = 1.5;
    this->def_face_min = Size(50, 50);
    this->def_eye_min = 0.3;
    this->def_smile_min = 0.4;
    this->def_eye_max = 0.5;
    this->def_smile_max = 0.55;
}

FaceDetector::~ FaceDetector() {
    for (auto it = cascades.begin(); it != cascades.end(); it++) {
        delete it->second;
    }
    cascades.clear();
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

void FaceDetector::detectObject(CascadeClassifier &classifier, const cv::Mat &grayImage, std::vector<cv::Rect> &rects,
                                double scaleFactor,
                                cv::Size minSize, cv::Size maxSize) {
    if (!classifier.empty() || grayImage.channels() > 1) {
        classifier.detectMultiScale(grayImage, rects, scaleFactor, 2, 0 | CASCADE_SCALE_IMAGE, minSize, maxSize);
    }
}

void FaceDetector::removeArtifactsFaces(cv::Mat &grayImage, std::vector<cv::Rect> &rects) {
    if (grayImage.channels() > 1 || !isLoaded_eye()) {
        return;
    }
    for (int i = 0; i < rects.size(); i++) {
        vector<Rect> eyes;
        detectObject(*cascades[EYE], grayImage, eyes, def_scaleFactor,
                     Size(grayImage.cols * def_eye_min, grayImage.rows * def_eye_min),
                     Size(grayImage.cols * def_eye_max, grayImage.rows * def_eye_max));
        if (eyes.size() < 2) {
            rects.erase(rects.begin() + i);
            i--;
        }
    }
}

void FaceDetector::detectFace(const cv::Mat &originalImage, std::vector<cv::Rect> rects, bool detectAllDegreese,
                              bool removeArtifacts) {
    if (isLoaded_face()) {
        Mat grayImage = toGrayscale(originalImage);
        detectObject(*cascades[FACE], grayImage, rects, def_scaleFactor, def_face_min, def_face_max);
        if (removeArtifacts) {
            removeArtifactsFaces(grayImage, rects);
        }
    }
}

void FaceDetector::detectEye(const cv::Mat &originalImage, std::vector<cv::Rect> rects) {
    if (isLoaded_eye()) {
        Mat grayImage = toGrayscale(originalImage);
        detectObject(*cascades[EYE], grayImage, rects, def_scaleFactor,
                     Size(grayImage.cols * def_eye_min, grayImage.rows * def_eye_min),
                     Size(grayImage.cols * def_eye_max, grayImage.rows * def_eye_max));
    }
}

void FaceDetector::detectSmile(const cv::Mat &originalImage, std::vector<cv::Rect> rects) {
    if (isLoaded_smile()) {
        Mat grayImage = toGrayscale(originalImage);
        detectObject(*cascades[SMILE], grayImage, rects, def_scaleFactor,
                     Size(grayImage.cols * def_smile_min, grayImage.rows * def_smile_min),
                     Size(grayImage.cols * def_smile_min, grayImage.rows * def_smile_max));
    }
}

Mat FaceDetector::getFace(const cv::Mat &image, const cv::Rect &rect, bool normalize) {
    Mat roi = image(rect);
    if (normalize) {
        roi = normalizeFace(roi);
    }
    return roi;
}


void FaceDetector::getFaces(const cv::Mat &image, std::vector<PersonFace *> &persons, bool detectAllDegreese,
                            bool normalized) {
    if (isLoaded_face() && isLoaded_eye()) {
        Mat grayImage = toGrayscale(image);
        vector<Rect> rects;
        detectObject(*cascades[FACE], grayImage, rects, def_scaleFactor, def_face_min, def_face_max);

        //remove artifacts
        for (int i = 0; i < rects.size(); i++) {
            vector<Rect> eyes;
            detectObject(*cascades[EYE], grayImage(rects[i]), eyes, def_scaleFactor,
                         Size(rects[i].width * def_eye_min, rects[i].height * def_eye_min),
                         Size(rects[i].width * def_eye_max, rects[i].height * def_eye_max));
            if (eyes.size() < 1) {
                rects.erase(rects.begin() + i);
                i--;
            } else {
                PersonFace *personFace;
                //if find only 1 eye
                if (normalized && eyes.size() < 2) {
                    eyes.push_back(copyEye(eyes[0],rects[i]));
                }
                Mat norm_face = normalizeFace(image(rects[i]), eyes[0], eyes[1]);
                personFace = new PersonFace(norm_face, 0);
                personFace->setEyes(eyes[0], eyes[1]);
                persons.push_back(personFace);
            }
        }
    }
}

Mat FaceDetector::normalizeFace(const cv::Mat &image) {
    vector<Rect> eyes;
    detectEye(image, eyes);
    if (eyes.size() > 2) {
        return normalizeFace(image, eyes[0], eyes[1]);
    } else {
        return image;
    }
}

Mat FaceDetector::normalizeFace(const cv::Mat &image, cv::Rect &eye_1, cv::Rect &eye_2) {
    float radians = getRotation(eye_1, eye_2);
    float degrees = toDegrees(radians);
    if (degrees > 15) {
        degrees = 15;
        radians = toRadians(degrees);
    } else if (degrees < -15) {
        degrees = -15;
        radians = toRadians(degrees);
    }

    float x1 = min(eye_1.x, eye_2.x);
    float y1 = min(eye_1.y, eye_2.y);
    float x2 = max(eye_1.x + eye_1.width, eye_2.x + eye_2.width);
    float width = x2 - x1;
    float height = image.rows - y1;


    Rect2f mask = Rect2f(x1, y1, width, height);

    Mat cutted = image(mask);
    eye_1.x -= mask.x;
    eye_1.y -= mask.y;
    eye_2.x -= mask.x;
    eye_2.y -= mask.y;

    Point2f center(cutted.cols / 2.0, cutted.rows / 2.0);
    Mat rot_mat = getRotationMatrix2D(center, degrees, 1.0);
    Mat rotaded;
    warpAffine(cutted, rotaded, rot_mat, cutted.size());

    rotateRect(eye_1, center, -radians);
    rotateRect(eye_2, center, -radians);

    return rotaded;
}

const Size &FaceDetector::getDef_face_min() const {
    return def_face_min;
}

void FaceDetector::setDef_face_min(const Size &def_face_min) {
    this->def_face_min = def_face_min;
}

const Size &FaceDetector::getDef_face_max() const {
    return def_face_max;
}

void FaceDetector::setDef_face_max(const Size &def_face_max) {
    this->def_face_max = def_face_max;
}

float FaceDetector::getDef_eye_min() const {
    return def_eye_min;
}

void FaceDetector::setDef_eye_min(float def_eye_min) {
    if (def_eye_min >= 0)
        this->def_eye_min = def_eye_min;
}

float FaceDetector::getDef_eye_max() const {
    return def_eye_max;
}

void FaceDetector::setDef_eye_max(float def_eye_max) {
    if (def_eye_max >= 0)
        def_eye_max = def_eye_max;
}

float FaceDetector::getDef_smile_min() const {
    return def_smile_min;
}

void FaceDetector::setDef_smile_min(float def_smile_min) {
    if (def_smile_min >= 0)
        this->def_smile_min = def_smile_min;
}

float FaceDetector::getDef_smile_max() const {
    return def_smile_max;
}

void FaceDetector::setDef_smile_max(float def_smile_max) {
    if (def_smile_max >= 0)
        this->def_smile_max = def_smile_max;
}

double FaceDetector::getDef_scaleFactor() const {
    return def_scaleFactor;
}

void FaceDetector::setDef_scaleFactor(double def_scaleFactor) {
    if (def_scaleFactor >= 0)
        this->def_scaleFactor = def_scaleFactor;
}
