//
// Created by Danil Kazimirov on 03.06.17.
//

#include <Utils.h>
#include <fstream>
#include <cmath>

using namespace cv;
using namespace std;

Mat toGrayscale(const Mat &src) {
    // Create and return grayscaled image:
    if (src.channels() == 3) {
        Mat dst;
        cvtColor(src, dst, COLOR_BGR2GRAY);
        return dst;
    } else {
        return src;
    }
}

bool isValidPath(const string &path) {
    fstream fin(path);
    if (fin.is_open()) {
        fin.close();
        return true;
    } else {
        return false;
    }
}

Point2f getCenter(const Rect &rect) {
    return Point2f(rect.x + rect.width / 2.0, rect.y + rect.height / 2.0);
}

float getRotation_radians(const Rect &rect1, const Rect &rect2) {
    float angle = 0;
    auto p1 = getCenter(rect1);
    auto p2 = getCenter(rect2);

    if (p1.x >= p2.x)
        angle = atan((p1.y - p2.y) / (p1.x - p2.x));
    else
        angle = atan((p2.y - p1.y) / (p2.x - p1.x));
    return angle;
}

float toDegrees(float radians) {
    return radians / M_PI * 180.0;
}

float toRadians(float degree) {
    return degree * M_PI / 180.0;
}

Size getSize(const Mat &M, float scale) {
    return Size(M.cols * scale, M.rows * scale);
}

Size getSize(const Rect &R, float scale) {
    return Size(R.width * scale, R.height * scale);
}


void rotateRect(cv::Rect &R, const cv::Point2f center, float angle) {
    float ca = cos(angle);
    float sa = sin(angle);
    //copy val
    float dx = R.x - center.x;
    float dy = R.y - center.y;
    //move to new CS
    R.x = ca * dx - sa * dy + center.x;
    R.y = sa * dx + ca * dy + center.y;
}

Rect copyLeftEye(const Rect &eye, const Rect &frame) {
    Rect rigthEye;
    rigthEye.x = (eye.x + eye.width);

    if (rigthEye.x > frame.width) {
        rigthEye.x = frame.width;
    }

    rigthEye.y = eye.y;

    if (rigthEye.x + eye.width > frame.width) {
        rigthEye.width = frame.width - rigthEye.x;
    } else {
        rigthEye.width = eye.width;
    }

    rigthEye.height = eye.height;
    return rigthEye;

}

Rect copyRigthEye(const Rect &eye, const Rect &frame) {
    Rect leftEye;
    leftEye.x = (eye.x - eye.width);

    if (leftEye.x < 0) {
        leftEye.x = 0;
    }

    leftEye.y = eye.y;
    leftEye.height = eye.height;
    leftEye.width = eye.width;
    return leftEye;

}


Rect copyEye(const Rect &eye, const Rect &frame) {
    if (eye.x < frame.width / 2) {
        return copyLeftEye(eye, frame);
    } else {
        return copyRigthEye(eye, frame);
    }
}

void disableArea(Mat &image, const Rect &rect) {
    Point eye_center(rect.x + rect.width / 2, rect.y + rect.height / 2);
    int radius = max(rect.width, rect.height);
    circle(image, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
}