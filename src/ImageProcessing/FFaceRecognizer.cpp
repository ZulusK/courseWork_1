//
// Created by Danil Kazimirov on 05.06.17.
//

#include <FFaceRecognizer.h>
#include <FPerson.h>
#include <Utils.h>

using namespace std;
using namespace cv;
using namespace face;


FFaceRecognizer::FFaceRecognizer(const std::string &dirPath, const cv::Size &sizeOfImage, int numOfComponents,
                                 double threahold) {
    this->recognizer = createFisherFaceRecognizer();
    set_threahold(threahold);
    set_num_of_components(numOfComponents);
    load(dirPath);
    this->imageScaleSize = sizeOfImage;
}


FFaceRecognizer::FFaceRecognizer(const Size &imageScaleSize) {
    this->imageScaleSize = imageScaleSize;
    this->recognizer = createFisherFaceRecognizer();
}

FFaceRecognizer::~FFaceRecognizer() {
    this->recognizer.release();
}

void FFaceRecognizer::set_num_of_components(int number) {
    if (number > 0) {
        recognizer->setNumComponents(number);
    }
}

void FFaceRecognizer::set_threahold(double threahold) {
    if (threahold > 0) {
        recognizer->setThreshold(threahold);
    }
}

bool FFaceRecognizer::load(const std::string &loadPath) {
    if (isFileExist(loadPath)) {
        recognizer->load(loadPath);
        return true;
    } else {
        return false;
    }
}

bool FFaceRecognizer::save(const std::string &savePath) {
    if (!recognizer->empty()) {
        recognizer->save(savePath);
        return true;
    } else {
        return false;
    }
}

int FFaceRecognizer::recognize(const cv::Mat &face) {
    if (recognizer->getProjections().empty() || face.empty())
        return -1;
    Mat scaled_image;
    resize(face, scaled_image, imageScaleSize);
    int label = 1;
    if (scaled_image.channels() > 1) {
        Mat gray;
        label = recognizer->predict(toGray(scaled_image));
        gray.release();
    } else {
        label = recognizer->predict(scaled_image);
    }
    scaled_image.release();
    return label;
}

int FFaceRecognizer::recognize(FPerson &personFace) {
    if (recognizer->getProjections().empty() || personFace.get_image().empty())
        return -1;
    Mat face = personFace.get_image();
    return recognize(face);
}

int FFaceRecognizer::get_num_of_components() {
    return recognizer->getNumComponents();
}

double FFaceRecognizer::get_threahold() {
    return recognizer->getThreshold();
}

bool FFaceRecognizer::learn(FPerson &personFace, int label) {
    return learn(personFace.get_image(), label);
}

bool FFaceRecognizer::learn(const cv::Mat &face, int label) {
    vector<Mat> images;
    images.push_back(face);
    vector<int> labels;
    labels.push_back(label);
    return learn(images, labels);
}

bool FFaceRecognizer::learn(const vector<Mat> &images, const vector<int> labels) {
    vector<Mat> scaled_images;
    vector<int> newLabels;
    for (int i = 0; i < images.size(); i++) {
        if (!images[i].empty()) {
            Mat scaledImage;
            resize(images[i], scaledImage, imageScaleSize);
            Mat gray = toGray(scaledImage);
            scaled_images.push_back(gray);
            newLabels.push_back(labels[i]);
            scaledImage.release();
            gray.release();
        }
    }
    if (scaled_images.size() == 0) {
        return false;
    } else {
        recognizer->train(scaled_images, labels);
        for (int i = 0; i < scaled_images.size(); i++) {
            scaled_images[i].release();
        }
        return true;
    }
}


cv::Size FFaceRecognizer::get_size_of_image() {
    return this->imageScaleSize;
}