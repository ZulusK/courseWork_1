#include <Facecope.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <FaceDetector.h>
#include <Picture.h>
#include <iostream>
#include <PersonFace.h>

using namespace std;
using namespace cv;

String window_name = "Capture - Face detection";

int counter = 0;

void detectAndDisplay(Mat &frame, FaceDetector &detector, bool save) {
    Picture picture(frame, &detector, NULL);
    picture.detect_persons(30,15);

    auto rects = picture.get_persons_rects();
    auto people = picture.get_persons_faces();
    auto faces = picture.get_persons();
    cout << people.size() << endl;
    //-- Detect faces
    for (size_t i = 0; i < faces.size(); i++) {
        rectangle(frame, faces[i].frame, Scalar(255, 0, 255));
        people[i]->normalize();
        imshow("human" + to_string(i), faces[i].personFace->get_face_rgb());
    }

    imshow(window_name, frame);
    rects.clear();
    people.clear();
}


int main(int argc, char **argv) {
    FaceDetector detector("/home/zulus/Projects/progbase3/src/lbpcascades/","/home/zulus/Projects/progbase3/src/haarcascades/");
    if (!detector.isLoaded_face()) {
        cout << "Detector is not loaded" << endl;
        return EXIT_FAILURE;
    }
//    Mat frame = imread("/home/zulus/Projects/progbase3/res/people.jpg");
    Mat frame;
//    detectAndDisplay(frame, detector, true);
//    char c = (char) waitKey(0);
    VideoCapture capture;
//
    capture.open(0);
    if (!capture.isOpened()) {
        cout << "--(!)Error opening video capture" << endl;
        return -1;
    }

    while (capture.read(frame)) {
        if (frame.empty()) {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        bool save = false;
        char c = (char) waitKey(20);
        if (c == 27) { break; }
        else if (c == '\n') {
            save = true;
        }

        //-- 3. Apply the classifier to the frame
        {
            detectAndDisplay(frame, detector, save);
        }
        frame.release();
    }
    return 0;
}