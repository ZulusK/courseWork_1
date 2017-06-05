//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FACECOPE_PERSONRECOGNIZER_H
#define FACECOPE_PERSONRECOGNIZER_H

#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <Facecope.h>

enum {
    FACE_WIDTH = 200,
    FACE_HEIGTH = 200,
};

/**
 * @brief defines face recognizer class
 */
class PersonRecognizer {
public:

    PersonRecognizer(const std::string &storagePath);

    void recognize(std::map<long, Face> persons);
};


#endif
