//
// Created by Danil Kazimirov on 04.06.17.
//

#ifndef FISHERFACE_FACECOPE_H
#define FISHERFACE_FACECOPE_H

#include <Picture.h>
#include <FaceDetector.h>
#include <PersonFace.h>
#include <PersonRecognizer.h>

namespace facecope {
    class Picture;

    class PersonFace;

    class PersonRecognizer;

    class FaceDetector;

    struct Face;
}

enum {
    NOT_RECOGNIZED = -0xFFFF
};
struct facecope::Face {
    facecope::PersonFace *personFace;
    cv::Rect frame;
    long hash;
};
#endif //FISHERFACE_FACECOPE_H
