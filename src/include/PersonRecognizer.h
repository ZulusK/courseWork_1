//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_PERSONRECOGNIZER_H
#define FISHERFACE_PERSONRECOGNIZER_H

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
class facecope::PersonRecognizer {
public:

    PersonRecognizer(const std::string &storagePath);

    void recognize(std::map<long, facecope::Face> persons);
};


#endif //FISHERFACE_PERSONRECOGNIZER_H
