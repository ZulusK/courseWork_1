//
// Created by Danil Kazimirov on 04.06.17.
//

#include <Picture.h>
#include <PersonFace.h>
#include <PersonRecognizer.h>
#include <FaceDetector.h>
#include <opencv2/imgcodecs.hpp>
#include <unordered_set>
#include <Facecope.h>
#include <iostream>
#include <opencv/cv.hpp>

using namespace cv;
using namespace std;

Picture::Picture(const cv::Mat &image, FaceDetector *detector,
                 PersonRecognizer *recognizer) {
    set_detector(detector);
    set_recognizer(recognizer);
    if (image.empty()) {
        this->originalImage = Mat::zeros(1, 1, CV_8UC1);
    } else {
        this->originalImage = image.clone();
    }
    detected = false;
}

Picture::Picture(const std::string &path, FaceDetector *detector,
                 PersonRecognizer *recognizer) {
    set_detector(detector);
    set_recognizer(recognizer);
    this->originalImage = imread(path);
    if (this->originalImage.empty()) {
        this->originalImage.release();
        this->originalImage = Mat::zeros(1, 1, CV_8UC1);
    }
    detected = false;
}

Picture::~Picture() {
    clearPersons();
    this->originalImage.release();
}

void Picture::clearPersons() {
    for (auto it = persons.begin(); it != persons.end(); it++) {
        delete it->second.personFace;
    }
    persons.clear();
}

FaceDetector *Picture::get_detector() const {
    return detector;
}

void Picture::set_detector(FaceDetector *detector) {
    if (detector) {
        this->detector = detector;
    } else {
        this->detector = NULL;
    }
}

PersonRecognizer *Picture::get_recognizer() const {
    return recognizer;
}

void Picture::set_recognizer(PersonRecognizer *recognizer) {
    if (recognizer) {
        this->recognizer = recognizer;
    } else {
        this->recognizer = NULL;
    };
}

void Picture::detect_persons(int angleRange, int angleStep) {
    if (!detected && detector && !empty()) {
        clearPersons();
        detected = true;
        detector->detect_PersonFace(originalImage, persons, angleRange, angleStep);
    }
}

void Picture::recognize_persons() {
    if (recognizer && !empty()) {
        recognizer->recognize(persons);
    }
}

bool Picture::empty() {
    return originalImage.empty();
}

bool Picture::recognized() {
    return !persons.empty();
}

bool Picture::recognize(bool allDegree) {
    detect_persons(15,15);
    recognize_persons();
}

std::vector<cv::Rect> Picture::get_persons_rects() {
    vector<Rect> rects;
    for (auto it = persons.begin(); it != persons.end(); it++) {
        rects.push_back(it->second.frame);
    }
    return rects;
}

std::vector<PersonFace *> Picture::get_persons_faces() {
    vector<PersonFace *> faces;
    int i = 0;
    for (auto it = persons.begin(); it != persons.end(); it++, i++) {
        PersonFace *pf = it->second.personFace;
        faces.push_back(it->second.personFace);
    }
    return faces;
}

std::vector<Face> Picture::get_persons() {
    vector<Face> faces;
    for (auto it = persons.begin(); it != persons.end(); it++) {
        faces.push_back(Face{.personFace=it->second.personFace, .frame=it->second.frame});
    }
    return faces;
}