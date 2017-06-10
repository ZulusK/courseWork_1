//
// Created by Danil Kazimirov on 05.06.17.
//

#include <FFaceDetector.h>
#include <FImage.h>
#include <Utils.h>
#include <FFaceArea.h>
#include <iostream>
#include <opencv/cv.hpp>

using namespace std;
using namespace cv;

FFaceDetector::FFaceDetector(const string &cascadesDir_face_haar, const string &cascadesDir_face_lbp,
                             const string &cascadesDir_eye_haar) {
    if (isFileExist(cascadesDir_face_haar)) {
        this->classifiers[FACE_HAAR] = new CascadeClassifier();
        this->classifiers[FACE_HAAR]->load(cascadesDir_face_haar);
    } else {
        cout << cascadesDir_face_haar << " was not loaded" << endl;
    }
    if (isFileExist(cascadesDir_face_lbp)) {
        this->classifiers[FACE_LBP] = new CascadeClassifier();
        this->classifiers[FACE_LBP]->load(cascadesDir_face_lbp);
    } else {
        cout << cascadesDir_face_lbp << " was not loaded" << endl;
    }
    if (isFileExist(cascadesDir_eye_haar)) {
        this->classifiers[EYES_HAAR] = new CascadeClassifier();
        this->classifiers[EYES_HAAR]->load(cascadesDir_eye_haar);
    } else {
        cout << cascadesDir_eye_haar << " was not loaded" << endl;
    }
}

FFaceDetector::~FFaceDetector() {
    for (auto it = classifiers.begin(); it != classifiers.end(); it++) {
        delete it->second;
    }
    classifiers.clear();
}

bool FFaceDetector::isLoaded(int what) {
    return classifiers.find(what) != classifiers.end() && !classifiers[what]->empty();
}

void
FFaceDetector::detect_faces(const cv::Mat &image, std::vector<FFaceArea *> &faces, bool removeFaceWithoutEye,
                            int cascade_type, int steps, int angle_range,
                            double scaleFactor,
                            cv::Size min_size_ratio, cv::Size
                            max_size_ratio) {
    //convert image to gray
    Mat gray_image = toGray(image);
    //if search only in original rotation
    if (steps <= 2) {
        find_faces(gray_image, faces, removeFaceWithoutEye, cascade_type, scaleFactor, min_size_ratio,
                   max_size_ratio);
    } else {
        //if search on range degree
        find_faces(gray_image, faces, removeFaceWithoutEye, cascade_type, steps, angle_range, scaleFactor,
                   min_size_ratio,
                   max_size_ratio);
    }
    gray_image.release();
}

void FFaceDetector::detect_faces(FImage &image, bool removeFaceWithoutEye, int cascade_type, int steps, int angle_range,
                                 double scaleFactor,
                                 Size min_size_ratio, Size
                                 max_size_ratio) {
    if (!image.empty()) {
        vector<FFaceArea *> faces;
        detect_faces(image.get_image(), faces, removeFaceWithoutEye, cascade_type, steps, angle_range);
        image.add_face(faces);
    }
}

void FFaceDetector::find_faces(cv::Mat &image,
                               std::vector<FFaceArea *> &faces,
                               bool removeFaceWithoutEye,
                               int cascade_type,
                               int steps, int range,
                               float scaleFactor,
                               cv::Size min_size_ratio, cv::Size
                               max_size_ratio) {
    //in each iteration angle will be increse by this
    int angleIncrement = range * 2 / (steps - 1);
    //starts from
    int leftBound = -range;
    //nd with
    int rigthBound = range;

    vector<Rect> bounds;
    vector<Rect> eyes_1;
    vector<Rect> eyes_2;
    for (int currAngle = leftBound; currAngle <= rigthBound; currAngle += angleIncrement) {
        bounds.clear();
        eyes_1.clear();
        eyes_2.clear();
        //rotate image
        Mat rotatedImage = rotate(image, currAngle, true);
        //detect bounds
        if (cascade_type == LBP && isLoaded(FACE_LBP)) {
            //if use LBP
            detect_object(rotatedImage, *classifiers[FACE_LBP], bounds, scaleFactor, min_size_ratio, max_size_ratio);
        } else if (isLoaded(FACE_HAAR)) {
            //if use HAAR
            detect_object(rotatedImage, *classifiers[FACE_HAAR], bounds, scaleFactor, min_size_ratio, max_size_ratio);
        }
        //detect eyes
        //remove artifacts
        get_faces_attr(rotatedImage, bounds, removeFaceWithoutEye, eyes_1, eyes_2);
        Point center = getCenter(image);
        //remove area
        for (auto i = 0; i < bounds.size(); i++) {
            rotateRect(bounds[i], center, toRadians(currAngle));
            disableArea(image, bounds[i]);
        }
        create_faceAreas_rotated(faces, bounds, eyes_1, eyes_2, currAngle, center);
//        imshow(to_string(currAngle), rotatedImage);
    }
}

void FFaceDetector::detect_object(Mat &image_gray,
                                  CascadeClassifier &classifier,
                                  vector<Rect> &rects,
                                  float scaleFactor,
                                  Size min_size_ratio,
                                  Size max_size_ratio) {
    if (!classifier.empty() && image_gray.channels() == 1) {
        classifier.detectMultiScale(image_gray, rects, scaleFactor, 3, 0 | CV_HAAR_SCALE_IMAGE, min_size_ratio,
                                    max_size_ratio);
    } else {
        cout << "NOT A GRAY" << endl;
    }
}

void FFaceDetector::find_faces(Mat &image, vector<FFaceArea *> &faces, bool removeFaceWithoutEye, int cascade_type,
                               float scaleFactor,
                               Size min_size_ratio, Size max_size_ratio) {

    vector<Rect> bounds;
    vector<Rect> eyes_1;
    vector<Rect> eyes_2;
    //detect bounds
    if (cascade_type == LBP && isLoaded(FACE_LBP)) {
        //if use LBP
        detect_object(image, *classifiers[FACE_LBP], bounds, scaleFactor, min_size_ratio, max_size_ratio);
    } else if (isLoaded(FACE_HAAR)) {
        //if use HAAR
        detect_object(image, *classifiers[FACE_HAAR], bounds, scaleFactor, min_size_ratio, max_size_ratio);
    }
    //detect eyes
    //remove artifacts
    get_faces_attr(image, bounds, removeFaceWithoutEye, eyes_1, eyes_2);
    create_faceAreas(faces, bounds, eyes_1, eyes_2);
}

void FFaceDetector::create_faceAreas(vector<FFaceArea *> &faces, vector<Rect> &bounds,
                                     vector<Rect> &eyes_1, vector<Rect> &eyes_2) {
    for (int i = 0; i < bounds.size(); i++) {
        auto faceArea = new FFaceArea(bounds[i], eyes_1[i], eyes_2[i]);
        faces.push_back(faceArea);
    }
}

void
FFaceDetector::get_faces_attr(Mat &image_gray, vector<Rect> &bounds, bool removeFaceWithoutEye, vector<Rect> &eyes_1,
                              vector<Rect> &eyes_2) {
    vector<Rect> eye_bounds;
    //if can find eyes
    if (isLoaded(EYES_HAAR)) {
        for (int i = 0; i < bounds.size(); i++) {
            eye_bounds.clear();
            //create eye search area (top half of face)
            Mat eyeArea = image_gray(Rect(bounds[i].x, bounds[i].y, bounds[i].width, bounds[i].height / 2));
            //find eyes
            detect_object(eyeArea, *classifiers[EYES_HAAR], eye_bounds, 1.1, Size(), Size());
            eyeArea.release();
            //process collected data
            if (eye_bounds.size() == 0) {
                //if didn't find, erase face
                if (removeFaceWithoutEye) {
                    bounds.erase(bounds.begin() + i);
                    i--;
                } else {
                    eyes_1.push_back(Rect(-1, -1, 0, 0));
                    eyes_2.push_back(Rect(-1, -1, 0, 0));
                }
            } else if (eye_bounds.size() == 1) {
                //if find only 1 eye, make second eye invalid
                eyes_1.push_back(eye_bounds[0]);
                eyes_2.push_back(Rect(-1, -1, 0, 0));
            } else {
                //add two eyes
                eyes_1.push_back(eye_bounds[0]);
                eyes_2.push_back(eye_bounds[1]);
            }
        }
    } else {
        //emulate eyes
        for (int i = 0; i < bounds.size(); i++) {
            eyes_1.push_back(Rect(-1, -1, 0, 0));
            eyes_2.push_back(Rect(-1, -1, 0, 0));
        }
    }
}

void FFaceDetector::create_faceAreas_rotated(vector<FFaceArea *> &faces, vector<Rect> &bounds,
                                             vector<Rect> &eyes_1, vector<Rect> &eyes_2, int angle,
                                             const Point &center) {
    for (int i = 0; i < bounds.size(); i++) {
        auto faceArea = new FFaceArea(bounds[i], eyes_1[i], eyes_2[i], NULL, angle, center);
        faces.push_back(faceArea);
    }
}
