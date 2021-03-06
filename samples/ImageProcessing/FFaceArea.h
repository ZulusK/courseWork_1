//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_FFACE_H
#define FACECOPE_FFACE_H

#include <Facecope.h>
#include <FPerson.h>
#include <opencv2/imgproc.hpp>

class FFaceArea {
    cv::Rect frame;
    cv::Rect rotated_frame;
    cv::Point centerOfRotation;
    FPerson *person;
    long ID;
    FImage *parent;
    int angle;
    bool normalized;
private:
    void normalize();

public:
    FFaceArea(const cv::Rect &frame, cv::Rect &eye_1, cv::Rect &eye_2, FImage *parent=NULL,int angle=0, const cv::Point & centerOfRotation=cv::Point());

    ~FFaceArea();

    FPerson *get_person();

    FImage *get_parent();

    cv::Mat get_image();

    void set_parent(FImage &parent);

    long get_areaID();

    void set_areaID(long id);

    cv::Size size();

    void set_frame(const cv::Rect &frame);

    const cv::Rect get_frame();

    int get_angle() const;
};


#endif //FACECOPE_FFACE_H
