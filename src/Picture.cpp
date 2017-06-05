//
// Created by Danil Kazimirov on 04.06.17.
//

#include <Picture.h>
#include <PersonFace.h>
#include <PersonRecognizer.h>
#include <FaceDetector.h>
#include <opencv2/imgcodecs.hpp>
#include <unordered_set>

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
}

Picture::Picture(const std::string &path, FaceDetector *detector,
                           PersonRecognizer *recognizer) {
    set_detector(detector);
    set_recognizer(recognizer);
    this->originalImage = imread(path);
    if (this->originalImage.empty()) {
        this->originalImage = Mat::zeros(1, 1, CV_8UC1);
    }
}

Picture::~Picture() {
    clearPersons();
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

void Picture::detect_persons() {
    if (detector && !empty()) {
        clearPersons();
        detector->detect_PersonFace(originalImage, persons, true);
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


bool Picture::recognize() {
    detect_persons();
    recognize_persons();
}