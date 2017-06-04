//
// Created by Danil Kazimirov on 04.06.17.
//

#include <Picture.h>
#include <opencv2/imgcodecs.hpp>
#include <unordered_set>

using namespace cv;
using namespace std;

facecope::Picture::Picture(const cv::Mat &image, facecope::FaceDetector *detector,
                           facecope::PersonRecognizer *recognizer) {
    set_detector(detector);
    set_recognizer(recognizer);
    if (image.empty()) {
        this->originalImage = Mat::zeros(1, 1, CV_8UC1);
    } else {
        this->originalImage = image.clone();
    }
}

facecope::Picture::Picture(const std::string &path, facecope::FaceDetector *detector,
                           facecope::PersonRecognizer *recognizer) {
    set_detector(detector);
    set_recognizer(recognizer);
    this->originalImage = imread(path);
    if (this->originalImage.empty()) {
        this->originalImage = Mat::zeros(1, 1, CV_8UC1);
    }
}

facecope::Picture::~Picture() {
    clearPersons();
}

void facecope::Picture::clearPersons() {
    for (auto it = persons.begin(); it != persons.end(); it++) {
        delete it->second.personFace;
    }
    persons.clear();
}

facecope::FaceDetector *facecope::Picture::get_detector() const {
    return detector;
}

void facecope::Picture::set_detector(facecope::FaceDetector *detector) {
    if (detector) {
        this->detector = detector;
    } else {
        this->detector = NULL;
    }
}

facecope::PersonRecognizer *facecope::Picture::get_recognizer() const {
    return recognizer;
}

void facecope::Picture::set_recognizer(facecope::PersonRecognizer *recognizer) {
    if (recognizer) {
        this->recognizer = recognizer;
    } else {
        this->recognizer = NULL;
    };
}

void facecope::Picture::detect_persons() {
    if (detector && !empty()) {
        clearPersons();
        detector->detect_PersonFace(originalImage, persons, true);
    }
}

void facecope::Picture::recognize_persons() {
    if (recognizer && !empty()) {
        recognizer->recognize(persons);
    }
}

bool facecope::Picture::empty() {
    return originalImage.empty();
}

bool facecope::Picture::recognized() {
    return !persons.empty();
}


bool facecope::Picture::recognize() {
    detect_persons();
    recognize_persons();
}