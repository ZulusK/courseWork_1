//
// Created by Danil Kazimirov on 03.06.17.
//

#include <Facecope.h>
#include <Utils.h>

using namespace std;
using namespace cv;

facecope::PersonFace::PersonFace(const cv::Mat &original, const cv::Rect &eye_1, const cv::Rect &eye_2, long id = 0) {
    this->id = id;
    if (original.empty()) {
        this->face_rgb = Mat::zeros(1, 1, CV_8UC1);
    } else {
        if (eye_1.x < eye_2.x) {
            this->eyes[0] = eye_1;
            this->eyes[1] = eye_2;
        } else {
            this->eyes[0] = eye_2;
            this->eyes[1] = eye_1;
        }
        this->face_rgb = original;
        this->normalized = false;
    }
}

void facecope::PersonFace::normalize_rotatation() {

    //get angle of rotation
    float radians = -getRotation_radians(eyes[0], eyes[1]);
    float degrees = toDegrees(radians);
    if (degrees > ROTATE_FACE_MAX_ANGLE) {
        degrees = ROTATE_FACE_MAX_ANGLE;
        radians = toRadians(degrees);
    } else if (degrees < -ROTATE_FACE_MAX_ANGLE) {
        degrees = -ROTATE_FACE_MAX_ANGLE;
        radians = toRadians(degrees);
    }

    //get center of image
    Point2f center(face_rgb.cols / 2.0, face_rgb.rows / 2.0);
    //get rotation matrix
    Mat rot_mat = getRotationMatrix2D(center, degrees, 1.0);
    //copy face image
    Mat original = face_rgb.clone();
    //get new bounding rect
    cv::Rect bbox = cv::RotatedRect(center, original.size(), degrees).boundingRect();
    //rotate face
    warpAffine(original, face_rgb, rot_mat, bbox.size());

    //rotate eye
    rotateRect(eyes[0], center, radians);
    rotateRect(eyes[1], center, radians);
}

void facecope::PersonFace::normalize_size() {
    float x1 = min(eyes[0].x, eyes[1].x);
    float y1 = min(eyes[0].y, eyes[1].y);
    float x2 = max(eyes[0].x + eyes[0].width, eyes[1].x + eyes[1].width);
    float width = x2 - x1;
    float height = face_rgb.rows - y1;

    Rect2f mask = Rect2f(x1, y1, width, height);
    eyes[0].x -= mask.x;
    eyes[0].y -= mask.y;
    eyes[1].x -= mask.x;
    eyes[1].y -= mask.y;
    this->face_rgb = face_rgb(mask);
}

void facecope::PersonFace::normalize() {
    if (!this->normalized) {
        this->normalize_size();
        this->normalize_rotatation();
        //set flag
        this->normalized = true;
    }
}

~PersonFace();

long facecope::PersonFace::get_id() const {
    return id;
}

void facecope::PersonFace::set_id(long id) {
    this->id = id;
}

const cv::Mat &facecope::PersonFace::get_face_rgb() const {
    return face_rgb;
}

const cv::Rect *facecope::PersonFace::get_eyes() const {
    return eyes;
}

