//
// Created by Danil Kazimirov on 04.06.17.
//

#ifndef FISHERFACE_PICTURE_H
#define FISHERFACE_PICTURE_H

#include <Facecope.h>
#include <map>
#include <vector>

class facecope::Picture {
    cv::Mat originalImage;
    facecope::FaceDetector *detector;
    facecope::PersonRecognizer *recognizer;
    std::map<long, facecope::Face> persons;
private:
    void clearPersons();

    void detect_persons();

public:
    Picture(const std::string &path, facecope::FaceDetector *detector, facecope::PersonRecognizer *recognizer);

    Picture(const cv::Mat &image, facecope::FaceDetector *detector, facecope::PersonRecognizer *recognizer);

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


#endif //FISHERFACE_PICTURE_H
