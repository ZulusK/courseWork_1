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
    std::vector<Mat> faces;
    //-- Detect faces
    detector.detectFaces(frame,rects,true);
    detector.getFaces(frame,faces,false,true);
//    for (size_t i = 0; i < rects.size(); i++) {
//        rectangle(frame,rects[i],Scalar(255, 0, 255));
//    }
    //-- Show what you got
    if(!faces.empty())
    imshow(window_name, faces[0]);
}


int main(int argc, char **argv) {
    FaceDetector detector("../src/haarcascades/");
    if (!detector.isLoaded_face()) {
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