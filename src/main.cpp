#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <FaceDetector.h>
#include <iostream>

using namespace std;
using namespace cv;

String window_name = "Capture - Face detection";

void detectAndDisplay(Mat& frame,FaceDetector & detector) {
    std::vector<Rect> rects;
    //-- Detect faces
    detector.detectFaces(frame,rects);
    for (size_t i = 0; i < rects.size(); i++) {
//        Point center(rects[i].x + rects[i].width / 2, rects[i].y + rects[i].height / 2);
//        ellipse(frame, center, Size(rects[i].width / 2, rects[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
        rectangle(frame,rects[i],Scalar(255, 0, 255));
    }
    //-- Show what you got
    imshow(window_name, frame);
}


int main(int argc, char **argv) {
    FaceDetector detector("../src/haarcascades");
    if (!detector.isLoaded()) {
        cout << "Detector is not loaded" << endl;
        return EXIT_FAILURE;
    }
    VideoCapture capture;
    Mat frame;
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
        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame,detector);
        char c = (char) waitKey(10);
        if (c == 27) { break; } // escape
    }
    return 0;
}