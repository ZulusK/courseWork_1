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

    angle *= 180;
    angle /= M_PI;
    return angle;
}

Size getSize(const Mat &M, float scale) {
    return Size(M.cols * scale, M.rows * scale);
}

Size getSize(const Rect &R, float scale) {
    return Size(R.width * scale, R.height * scale);
}