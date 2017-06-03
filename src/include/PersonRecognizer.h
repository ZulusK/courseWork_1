//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_PERSONRECOGNIZER_H
#define FISHERFACE_PERSONRECOGNIZER_H
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
enum{
    FACE_ORIGINAL_WIDTH=150,
    FACE_ORIGINAL_EIGHT=150,
};
/**
 * @brief defines face recognizer class
 */
class PersonRecognizer {
private:


    PersonRecognizer(const std::string & storagePath);

};


#endif //FISHERFACE_PERSONRECOGNIZER_H
