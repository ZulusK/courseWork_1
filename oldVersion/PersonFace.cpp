//
// Created by Danil Kazimirov on 03.06.17.
//

#include <PersonFace.h>
#include <Utils.h>

using namespace std;
using namespace cv;

PersonFace::PersonFace(const cv::Mat &original, const cv::Rect &eye_1, const cv::Rect &eye_2, long id) {
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
        original.copyTo(face_rgb);
        this->normalized = false;
    }
}

void PersonFace::normalize_rotatation() {

    //get angle of rotation
    float radians = getRotation_radians(eyes[0], eyes[1]);
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
    Mat original;
    //get new bounding rect
    //rotate face
    warpAffine(face_rgb, original, rot_mat, face_rgb.size());
    face_rgb = original;

    //rotate eye
    rotateRect(eyes[0], center, -radians);
    rotateRect(eyes[1], center, -radians);
}

void PersonFace::normalize_size() {
    float x1 = min(eyes[0].x, eyes[1].x);
    float y1 = 1;
    float x2 = min(max(eyes[0].x + eyes[0].width, eyes[1].x + eyes[1].width), face_rgb.cols);
    float width = x2 - x1;
    float height = face_rgb.rows - 1;

    Rect2f mask = Rect2f(x1, 0, width, height);
    //normilize mask
    mask.x = max(1.0f, mask.x);
    mask.y = max(1.0f, mask.y);
    mask.height = min(face_rgb.rows - mask.y, mask.y + mask.height);
    mask.width = min(face_rgb.cols - mask.x, mask.x + mask.width);

    eyes[0].x -= mask.x;
    eyes[0].y -= mask.y;
    eyes[1].x -= mask.x;
    eyes[1].y -= mask.y;
    this->face_rgb = face_rgb(mask);
}

void PersonFace::normalize() {
    if (!this->normalized) {
        this->normalize_rotatation();
        this->normalize_size();
        rectangle(face_rgb, eyes[0], Scalar(255, 0, 0));
        rectangle(face_rgb, eyes[1], Scalar(255, 0, 0));
        //set flag
        this->normalized = true;
    }
}

PersonFace::~PersonFace() {
    this->face_rgb.release();
}

long PersonFace::get_id() const {
    return id;
}

void PersonFace::set_id(long id) {
    this->id = id;
}

const cv::Mat &PersonFace::get_face_rgb() const {
    return face_rgb;
}

const cv::Rect *PersonFace::get_eyes() const {
    return eyes;
}

