//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_FIMAGE_H
#define FACECOPE_FIMAGE_H

#include <Facecope.h>
#include <map>
#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>

class FImage {
    cv::Mat originalImage;
    std::vector<FFaceArea *> detectedFaces;
    bool is_persons_detected;
    bool is_persons_recognized;
private:
protected:
    void set_recognized_status(bool status);

    void set_detected_status(bool status);

    bool is_recognized();

    bool is_detected();

public:

    FImage(const std::string &filePath);

    FImage(const cv::Mat &image);

    ~FImage();

    std::vector<FFaceArea *> get_faces();

    FFaceArea *get_face(long id);

    void add_face(FFaceArea &face);

    void add_face(const std::vector<FFaceArea *> &faces);

    bool remove_face(long id);

    void clear();

    const cv::Mat &get_image() const;

    //todo serealization
    bool empty();
};

#endif //FACECOPE_FIMAGE_H
