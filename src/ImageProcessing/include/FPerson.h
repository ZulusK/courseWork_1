//
// Created by Danil Kazimirov on 05.06.17.
//

#ifndef FACECOPE_FPERSON_H
#define FACECOPE_FPERSON_H

#include <Facecope.h>
#include <opencv2/imgproc.hpp>


class FPerson {
    float rotation_degree;
    cv::Rect frame;
    Eye eye_left;
    Eye eye_rigth;
    FFaceArea *parent;
    bool normilized;
    long ID;
private:

public:
    FPerson(FFaceArea &parent, cv::Rect &eye_frame_1, cv::Rect &eye_frame_2, long id = -1);

    ~FPerson();

    cv::Mat get_image();

    FFaceArea *getParent();

    long get_ID();

    void set_ID(long id);

    const Eye &get_eye_left();

    const Eye &get_eye_rigth();

    void normalize();

    void set_eyes(cv::Rect &eye_frame_1, cv::Rect &eye_frame_2);

    void create_eyes(cv::Rect &eye_frame);
};


#endif //FACECOPE_FPERSON_H
