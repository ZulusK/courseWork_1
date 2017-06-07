//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_FACECOPE_H
#define FACECOPE_FACECOPE_H


#include <opencv2/core/types.hpp>

typedef struct {
    cv::Point pos;
    int radius;
} Eye;

//container for original RGB image and detected faces
class FImage;

//implements of methods for face detection
class FFaceDetector;


class FFaceRecognizer;

class FFaceArea;

class FPerson;

#endif //FACECOPE_FACECOPE_H
