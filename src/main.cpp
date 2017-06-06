//
// Created by Danil Kazimirov on 06.06.17.
//

#include <Facecope.h>
#include <FImage.h>
#include <FFaceDetector.h>
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <FFaceArea.h>
#include <FFaceRecognizer.h>
#include <Utils.h>

using namespace std;
using namespace cv;

string recognize(Mat &mat, FFaceRecognizer *recognizer) {
    int label = recognizer->recognize(mat);
    string box_text = format("Prediction = %d", label);
//    recognizer->learn(mat, 13);
    return box_text;
}

void videoDetection(FFaceDetector *detector, FFaceRecognizer *recognizer) {
    Mat cap_frame;
    VideoCapture capture;
    capture.open(0);
    while (capture.read(cap_frame)) {
        FImage *image = new FImage(cap_frame);
        detector->detect_faces(*image, true, -1, 0, 0);
        Mat frame = image->get_image().clone();
        auto faces = image->get_faces();
        for (int i = 0; i < faces.size(); i++) {
            Mat m_face = faces[i]->get_person()->get_image();
            circle(m_face, faces[i]->get_person()->get_eye_left().pos,
                   faces[i]->get_person()->get_eye_left().radius,
                   Scalar(255, 255, 0));
            circle(m_face, faces[i]->get_person()->get_eye_rigth().pos,
                   faces[i]->get_person()->get_eye_rigth().radius,
                   Scalar(45, 45, 200));
            // And now put it into the image:
            putText(frame, recognize(m_face, recognizer), Point(faces[i]->get_frame().x, faces[i]->get_frame().y),
                    FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);

            imshow(to_string(i), m_face);
            rectangle(frame, faces[i]->get_frame(), Scalar(255, 0, 0));
            m_face.release();
        }

        imshow("original", frame);
        delete image;
        frame.release();
        cap_frame.release();
        char c = (char) waitKey(20);
        if (c == 27) break;
    }
}

void imageDetection(FFaceDetector *detector) {
    FImage *image = new FImage("/home/zulus/Projects/progbase3/res/people3.jpg");
    detector->detect_faces(*image, false, -1, 20, 360);
    Mat frame = image->get_image().clone();
    auto faces = image->get_faces();
    for (int i = 0; i < faces.size(); i++) {
        Mat m_face = faces[i]->get_image().clone();
        circle(m_face, faces[i]->get_person()->get_eye_left().pos,
               faces[i]->get_person()->get_eye_left().radius,
               Scalar(255, 255, 0));
        circle(m_face, faces[i]->get_person()->get_eye_rigth().pos,
               faces[i]->get_person()->get_eye_rigth().radius,
               Scalar(45, 45, 200));
        imshow(to_string(i) + "hum", m_face);
        rectangle(frame, faces[i]->get_frame(), Scalar(255, 0, 0));
        m_face.release();
    }
    imshow("original", frame);
    delete image;
    frame.release();
    char c = (char) waitKey(0);
}

int main(int argc, char **argv) {
    FFaceDetector *detector = new FFaceDetector(
            "/home/zulus/Projects/progbase3/src/cascades/face_haar.xml",
            "/home/zulus/Projects/progbase3/src/cascades/face_lbp.xml",
            "/home/zulus/Projects/progbase3/src/cascades/eye_haar.xml");
    FFaceRecognizer *recognizer = new FFaceRecognizer();
    {
        vector<Mat> images;
        vector<int>labels;
        for (int i = 0; i < 10; i++) {
            Mat m;
            resize(imread("/home/zulus/Projects/progbase3/res/danil/Image" + to_string(i) + ".jpg"),m,recognizer->get_size_of_image());
            images.push_back(toGray(m));
            labels.push_back(13);
            resize(imread("/home/zulus/Projects/progbase3/res/danil/Image" + to_string(i) + ".jpg"),m,recognizer->get_size_of_image());
            images.push_back(toGray(m));
            labels.push_back(12);
        }
        recognizer->learn(images,labels);
    }

    if (detector->isLoaded(EYES_HAAR) && detector->isLoaded(FACE_HAAR) && detector->isLoaded(FACE_LBP)) {
        videoDetection(detector, recognizer);
//        imageDetection(detector);
    }
    delete detector;
    delete recognizer;
    return EXIT_SUCCESS;
}
