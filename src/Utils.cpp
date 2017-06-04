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
    if (src.channels() > 1) {
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


float getRotation(const Rect &rect1, const Rect &rect2) {
    float angle = 0;
    auto p1 = getCenter(rect1);
    auto p2 = getCenter(rect2);

    if (p1.x <= p2.x)
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
//    float old_x = dx;
//    float old_y = dy;
    R.x = ca * dx - sa * dy+center.x;
    R.y = sa * dx + ca * dy+center.y;
}

//Vec2D Vec2D_multByNumber(Vec2D a, double number) {
//    return (Vec2D){
//            .x = a.x * number,
//            .y = a.y * number
//    };
//}
//
//Point2f Vec2D_rotate(Point2f self, float radians) {
//    double ca = cosf(radians);
//    double sa = sinf(radians);
//    return (Point2f) {
//            .x = ca * self.x - sa * self.y,
//            .y = sa * self.x + ca * self.y
//    };
//}

//Point2f Vec2D_normalize(Point2f self) {
//    double length = Vec2D_length(self);
//    if (length == 0) return self;
//
//    return Vec2D_multByNumber(self, 1.0 / length);
//}
//
//double Vec2D_length(Point2f self) {
//    return sqrt(self.x * self.x + self.y * self.y);
//}
//
//Vec2D Vec2D_add(Vec2D a, Vec2D b) {
//    return (Vec2D){
//            .x = a.x + b.x,
//            .y = a.y + b.y
//    };
//}
//
//Vec2D Vec2D_substract(Vec2D a, Vec2D b) {
//    return (Vec2D){
//            .x = a.x - b.x,
//            .y = a.y - b.y
//    };
//}