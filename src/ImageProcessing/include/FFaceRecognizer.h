//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_FFACERECOGNIZER_H
#define FACECOPE_FFACERECOGNIZER_H

#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <Facecope.h>


class FFaceRecognizer {

private:
public:
    FFaceRecognizer(const std::string &dirPath);

    ~FFaceRecognizer();

    void recognize(std::vector<FPerson *> recognize);

    void recognize(FPerson &recognize);

};


#endif //FACECOPE_FFACERECOGNIZER_H
