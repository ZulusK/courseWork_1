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
    if (isValidPath(cascadeFolderPath + FACE_CASCADE_NAME_HAAR)) {
        cascades[FACE] = new CascadeClassifier();
        cascades[FACE]->load(cascadeFolderPath + FACE_CASCADE_NAME_HAAR);
    }
    if (isValidPath(cascadeFolderPath + EYE_CASCADE_NAME_HAAR)) {
        cascades[EYE] = new CascadeClassifier();
        cascades[EYE]->load(cascadeFolderPath + EYE_CASCADE_NAME_HAAR);
    }
    this->def_scaleFactor = 1.1;
//    this->def_face_min = Size(10, 10);
    this->def_eye_min = 0;
    this->def_eye_max = 0;
    this->def_rotate_step = 45;
}

FaceDetector::FaceDetector(const std::string &cascadeFolderPathLBP, const std::string &cascadeFolderPathHaar) {
    if (isValidPath(cascadeFolderPathLBP + FACE_CASCADE_NAME_LBP)) {
        cascades[FACE] = new CascadeClassifier();
        cascades[FACE]->load(cascadeFolderPathLBP + FACE_CASCADE_NAME_LBP);
    }
    if (isValidPath(cascadeFolderPathHaar + EYE_CASCADE_NAME_HAAR)) {
        cascades[EYE] = new CascadeClassifier();
        cascades[EYE]->load(cascadeFolderPathHaar + EYE_CASCADE_NAME_HAAR);
    }
    this->def_scaleFactor = 1.1;
//    this->def_face_min = Size(10, 10);
    this->def_eye_min = 0;
    this->def_eye_max = 0;
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
    if (!classifier.empty() && grayImage.channels() == 1) {
        classifier.detectMultiScale(grayImage, rects, scaleFactor, 2, 0 | CV_HAAR_SCALE_IMAGE, minSize, maxSize);
    }
}


void FaceDetector::remove_artifactedFaces(cv::Mat &grayImage, std::vector<cv::Rect> &rects,
                                          std::vector<vector<Rect>> &allEyes) {
    if (grayImage.channels() > 1) {
        return;
    }
    for (int i = 0; i < rects.size(); i++) {
        vector<Rect> eyes(2);
        //search eyes at top half of face
        Rect halg(0, 0, rects[i].width / 2, rects[i].height / 2);
        detectObject(*cascades[EYE], grayImage(rects[i]), eyes, def_scaleFactor,
//                     Size(rects[i].width * def_eye_min, rects[i].height * def_eye_min),
//                     Size(rects[i].width * def_eye_max, rects[i].height * def_eye_max));
                     Size(), Size());
        //if didn't find any eye, remove face
        if (eyes.size() == 0) {
            rects.erase(rects.begin() + i);
            eyes.clear();
            i--;
        } else {
            //add find eyes to list
            allEyes.push_back(eyes);
        }
    }
}


PersonFace *FaceDetector::createPersonFace(const cv::Mat imageRGB, cv::Rect &frameRect, std::vector<cv::Rect> &eyes) {
    Rect eye_1(0, 0, frameRect.width / 2, frameRect.height / 2);
    Rect eye_2(frameRect.width / 2, eye_1.y, frameRect.width / 2, frameRect.height / 2);
    if (eyes.size() > 0) {
        eye_1 = eyes[0];
        //if find only 1 eye, copy it
        if (eyes.size() == 1) {
            eye_2 = copyEye(eyes[0], frameRect);
        } else {
            eye_2 = eyes[1];
        }
    }
    PersonFace *personFace = new PersonFace(imageRGB(frameRect), eye_1, eye_2);
    return personFace;
}

void
FaceDetector::find_PersonsFaces(cv::Mat &imageGray, const cv::Mat &imageRGB, std::map<long, Face> &persons, float angle,
                                Point2f &center) {

    vector<Rect> allRects;
    detectObject(*cascades[FACE], imageGray, allRects, def_scaleFactor, def_face_min, def_face_max);
    vector<vector<Rect>> allEyes;
    //remove artifacts
    //find eyes
    remove_artifactedFaces(imageGray, allRects, allEyes);
    long shift = persons.size();
    //create persons
    for (long i = 0; i < allRects.size(); i++) {
        //fill area black
        disableArea(imageGray, allRects[i]);
        //create new person
        PersonFace *personFace = createPersonFace(imageRGB, allRects[i], allEyes[i]);
        //rotatet bounding rect
        rotateRect(allRects[i], center, -toRadians(angle));
        Face face{.personFace=personFace, .frame=allRects[i], .hash=shift + i};
        persons[face.hash] = face;
    }
    //add person to list
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
        persons[face.hash] = face;
    }
    imageGray.release();
}

void FaceDetector::detect_PersonFace(const cv::Mat &originalImage, std::map<long, Face> &persons, int angleRange,
                                     int angleStep) {
    if (isLoaded_face() && isLoaded_eye()) {
        if (angleRange > 0 && angleRange < 180) {
            //copy original image
            Mat copyGrayScale = toGrayscale(originalImage.clone());
            Mat copyRGB = originalImage.clone();
            {
                //create rotation matrix
                Point2f center(copyRGB.cols / 2.0, copyRGB.rows / 2.0);
                Mat rot_mat = getRotationMatrix2D(center, -angleRange, 1.0);
                Mat rotated;
                warpAffine(copyRGB, rotated, rot_mat, copyRGB.size());
                copyRGB = rotated;
                rotated.release();
                warpAffine(copyGrayScale, rotated, rot_mat, copyRGB.size());
                copyGrayScale = rotated;
                rotated.release();
            }
            Point2f center(copyRGB.cols / 2.0, copyRGB.rows / 2.0);
            Mat rot_mat = getRotationMatrix2D(center, angleStep, 1.0);
            //rotate image and detect persons in each angle
            for (int i = -angleRange; i <= angleRange; i += angleStep) {
                //get faces for this degrees
                find_PersonsFaces(copyGrayScale, copyRGB, persons, i, center);
                //rotate image
                {
                    Mat rotated;
                    warpAffine(copyRGB, rotated, rot_mat, copyRGB.size());
                    copyRGB = rotated;
                    rotated.release();
                    warpAffine(copyGrayScale, rotated, rot_mat, copyRGB.size());
                    copyGrayScale = rotated;
                    rotated.release();
                }
            }
//            imshow("gray", copyGrayScale);
            copyRGB.release();
            copyGrayScale.release();
//            imwrite("/home/zulus/Projects/progbase3/res/Gray.png",copyGrayScale);
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
        grayImage.release();
    }
}


void FaceDetector::detectEye(const cv::Mat &originalImage, std::vector<cv::Rect> &eyes) {
    if (isLoaded_eye()) {
        Mat grayImage = toGrayscale(originalImage);
        detectObject(*cascades[EYE], grayImage, eyes, def_scaleFactor,
                     Size(grayImage.cols * def_eye_min, grayImage.rows * def_eye_min),
                     Size(grayImage.cols * def_eye_max, grayImage.rows * def_eye_max));
        grayImage.release();
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

