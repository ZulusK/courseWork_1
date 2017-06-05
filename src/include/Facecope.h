//
// Created by Danil Kazimirov on 04.06.17.
//

#ifndef FACECOPE_H
#define FACECOPE_H

#include <opencv2/imgproc.hpp>

class FaceDetector;

class Picture;

class PersonFace;

class PersonRecognizer;


typedef struct {
    PersonFace *personFace;
    cv::Rect frame;
    long hash;
} Face;

enum {
    NOT_RECOGNIZED = -0xFFFF
};


#endif
