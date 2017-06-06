//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_FFACERECOGNIZER_H
#define FACECOPE_FFACERECOGNIZER_H

#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <Facecope.h>


class FFaceRecognizer {
    cv::Ptr<cv::face::BasicFaceRecognizer> recognizer;
    cv::Size imageScaleSize;
private:

public:
    FFaceRecognizer(const std::string &dirPath, const cv::Size &sizeOfImage = cv::Size(150, 150),
                    int numOfComponents = 80, double threahold = DBL_MAX);

    FFaceRecognizer(const cv::Size &imageScaleSize = cv::Size(150, 150));

    ~FFaceRecognizer();

    int recognize(const cv::Mat &face);

    int recognize(FPerson &personFace);

    bool learn(const cv::Mat &face, int label);

    bool learn(FPerson &pesonFace, int label);

    bool load(const std::string &loadPath);

    bool save(const std::string &savePath);

    void set_threahold(double threahold);

    double get_threahold();

    int get_num_of_components();

    void set_num_of_components(int number);

    bool learn(const std::vector<cv::Mat> &images, const std::vector<int> labels);
    cv::Size get_size_of_image();
};


#endif //FACECOPE_FFACERECOGNIZER_H
