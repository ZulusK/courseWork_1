#include <Facecope.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <FaceDetector.h>
#include <iostream>

using namespace std;
using namespace cv;

String window_name = "Capture - Face detection";

int counter = 0;
//
//void detectAndDisplay(Mat &frame, FaceDetector &detector, bool save) {
//    std::vector<Rect> rects;
//    std::vector<Mat> faces;
//    std::vector<PersonFace *> persons;
//    //-- Detect faces
////    detector.detectFaces(frame, rects, true);
//    detector.getFaces(frame, persons, false, true);
////    for (size_t i = 0; i < rects.size(); i++) {
////        rectangle(frame,rects[i],Scalar(255, 0, 255));
////    }
//    //-- Show what you got
//
//    if (!persons.empty()) {
//        for (int i = 0; i < persons.size(); i++) {
//            Mat image = persons[i]->getFaceRGB().clone();
//            rectangle(image, persons[i]->getEyes()[0], Scalar(255, 0, 255));
//            rectangle(image, persons[i]->getEyes()[1], Scalar(255, 0, 255));
//            imshow(window_name + to_string(i), image);
//            if (save) {
//                // сохраняем кадр в файл
//                char filename[100];
//                sprintf(filename, "../res/Image%d.jpg", counter);
//                if (imwrite(filename, persons[0]->getFaceRGB())) {
//                    printf("[i] capture... %s\n", filename);
//                }
//                counter++;
//            }
//        }
//    }
////    else {
//    imshow(window_name, frame);
////    }
//    for (int i = 0; i < persons.size(); i++) {
//        delete persons[i];
//    }
//    persons.clear();
//    rects.clear();
//}
//

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
        bool save = false;
        char c = (char) waitKey(20);
        if (c == 27) { break; }
        else if (c == '\n') {
            save = true;
        }

//        //-- 3. Apply the classifier to the frame
//        {
//            detectAndDisplay(frame, detector, save);
//        }
    }
    return 0;
}