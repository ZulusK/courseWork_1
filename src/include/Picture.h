//
// Created by Danil Kazimirov on 04.06.17.
//

#ifndef FACECOPE_PICTURE_H
#define FACECOPE_PICTURE_H

#include <Facecope.h>
#include <map>
#include <vector>
#include <opencv2/core/mat.hpp>

class Picture {
    cv::Mat originalImage;
    FaceDetector *detector;
    PersonRecognizer *recognizer;
    std::map<long, Face> persons;
private:
    void clearPersons();

    void detect_persons();

public:
    Picture(const std::string &path, FaceDetector *detector, PersonRecognizer *recognizer);

    Picture(const cv::Mat &image, FaceDetector *detector, PersonRecognizer *recognizer);

    ~Picture();

    FaceDetector *get_detector() const;

    void set_detector(FaceDetector *detector);

    PersonRecognizer *get_recognizer() const;

    void set_recognizer(PersonRecognizer *recognizer);

    void recognize_persons();

    bool empty();

    bool recognized();

    bool recognize();
};


#endif
