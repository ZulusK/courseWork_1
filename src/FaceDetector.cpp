//
// Created by Danil Kazimirov on 05.06.17.
//

#include <opencv/cv.hpp>
#include <Utils.h>
#include <iostream>
#include <Facecope.h>
#include <PersonFace.h>
#include <FaceDetector.h>

using namespace cv;
using namespace std;

enum {
    FACE = 0xA,
    EYE,
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
    this->def_scaleFactor = 1.5;
    this->def_face_min = Size(100, 100);
    this->def_eye_min = 0.15;
    this->def_eye_max = 0.5;
    this->def_rotate_step = 45;
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


void FaceDetector::detectObject(CascadeClassifier &classifier, const cv::Mat &grayImage,
                                std::vector<cv::Rect> &rects,
                                double scaleFactor,
                                cv::Size minSize, cv::Size maxSize) {
    if (!classifier.empty() || grayImage.channels() > 1) {
        classifier.detectMultiScale(grayImage, rects, scaleFactor, 2, 0 | CASCADE_SCALE_IMAGE, minSize, maxSize);
    }
}


void FaceDetector::remove_artifactedFaces(cv::Mat &grayImage, std::vector<cv::Rect> &rects,
                                          std::vector<vector<Rect>> &allEyes) {
    if (grayImage.channels() > 1) {
        return;
    }
    for (int i = 0; i < rects.size(); i++) {
        vector<Rect> eyes;
        detectObject(*cascades[EYE], grayImage, eyes, def_scaleFactor,
                     Size(grayImage.cols * def_eye_min, grayImage.rows * def_eye_min),
                     Size(grayImage.cols * def_eye_max, grayImage.rows * def_eye_max));
        //if didn't find any eye, remove face
        if (eyes.size() == 0) {
            rects.erase(rects.begin() + i);
            i--;
        } else {
            //add find eyes to list
            allEyes.push_back(eyes);
        }
    }
}


PersonFace *FaceDetector::createPersonFace(const cv::Mat imageRGB, cv::Rect &frameRect, std::vector<cv::Rect> &eyes) {
    Rect eye_1 = eyes[0];
    Rect eye_2;
    //if find only 1 eye, copy it
    if (eyes.size() == 1) {
        eye_2 = copyEye(eyes[0], frameRect);
    } else {
        eye_2 = eyes[1];
    }
    PersonFace *personFace = new PersonFace(imageRGB(frameRect), eye_1, eye_2);
    return personFace;
}

void FaceDetector::find_PersonsFaces(cv::Mat &imageGray, const cv::Mat &imageRGB, std::map<long, Face> &persons) {

    vector<Rect> allRects;
    detectObject(*cascades[FACE], imageGray, allRects, def_scaleFactor, def_face_min, def_face_max);
    vector<vector<Rect>> allEyes;
    //remove artifacts
    //find eyes
    remove_artifactedFaces(imageGray, allRects, allEyes);
    long shift = persons.size();
    //create persons
    for (long i = 0; i < allRects.size(); i++) {
        //create new person
        PersonFace *personFace = createPersonFace(imageRGB, allRects[i], allEyes[i]);
        Face face{.personFace=personFace, .frame=allRects[i], .hash=shift + i};
        //add person to list
        persons[shift + i] = face;
        disableArea(imageGray, allRects[i]);
    }
}

void FaceDetector::find_PersonsFaces(const cv::Mat &imageRGB, std::map<long, Face> &persons) {
    vector<Rect> allRects;
    Mat imageGray = toGrayscale(imageRGB);
    detectObject(*cascades[FACE], imageGray, allRects, def_scaleFactor, def_face_min, def_face_max);
    vector<vector<Rect>> allEyes;
    //remove artifacts
    //find eyes
    remove_artifactedFaces(imageGray, allRects, allEyes);
    long shift = persons.size();
    //create persons
    for (long i = 0; i < allRects.size(); i++) {
        //create new person
        PersonFace *personFace = createPersonFace(imageRGB, allRects[i], allEyes[i]);
        Face face{.personFace=personFace, .frame=allRects[i], .hash=shift + i};
        //add person to list
        persons[shift + i] = face;
    }
}

void FaceDetector::detect_PersonFace(const cv::Mat &originalImage, std::map<long, Face> &persons, bool allAngles) {
    if (isLoaded_face() && isLoaded_eye()) {
        if (allAngles) {
            //copy original image
            Mat copyGrayScale = toGrayscale(originalImage.clone());
            Mat copyRGB = originalImage.clone();
            //create rotation matrix
            Point2f center(originalImage.cols / 2.0, originalImage.rows / 2.0);
            Mat rot_mat = getRotationMatrix2D(center, def_rotate_step, 1.0);

            //rotate image and detect persons in each angle
            for (int i = 0; i < 360; i += def_rotate_step) {
                //get faces for this degrees
                find_PersonsFaces(copyGrayScale, copyRGB, persons);
                //rotate image
                cv::Rect bbox = cv::RotatedRect(center, originalImage.size(), i).boundingRect();
                Mat rotated;
                warpAffine(copyRGB, rotated, rot_mat, bbox.size());
                copyRGB = rotated;
                warpAffine(copyGrayScale, rotated, rot_mat, bbox.size());
                copyGrayScale;
            }
        } else {
            find_PersonsFaces(originalImage, persons);
        }
    }
}

void FaceDetector::detectFace(const cv::Mat &originalImage, std::vector<cv::Rect> rects, vector<vector<Rect>> &eyes) {
    if (isLoaded_face()) {
        Mat grayImage = toGrayscale(originalImage);
        detectObject(*cascades[FACE], grayImage, rects, def_scaleFactor, def_face_min, def_face_max);
        remove_artifactedFaces(grayImage, rects, eyes);
    }
}


void FaceDetector::detectEye(const cv::Mat &originalImage, std::vector<cv::Rect> &eyes) {
    if (isLoaded_eye()) {
        Mat grayImage = toGrayscale(originalImage);
        detectObject(*cascades[EYE], grayImage, eyes, def_scaleFactor,
                     Size(grayImage.cols * def_eye_min, grayImage.rows * def_eye_min),
                     Size(grayImage.cols * def_eye_max, grayImage.rows * def_eye_max));
    }
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


double FaceDetector::getDef_scaleFactor() const {
    return def_scaleFactor;
}

void FaceDetector::setDef_scaleFactor(double def_scaleFactor) {
    if (def_scaleFactor >= 0)
        this->def_scaleFactor = def_scaleFactor;
}

float FaceDetector::getDef_rotate_step() const {
    return def_rotate_step;
}

void FaceDetector::setDef_rotate_step(float def_rotate_step) {
    if (def_rotate_step > 0 && def_rotate_step < 180)
        this->def_rotate_step = def_rotate_step;
}

