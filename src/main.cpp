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

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    FFaceDetector *detector = new FFaceDetector(
            "/home/zulus/Projects/progbase3/src/cascades/face_haar.xml",
            "/home/zulus/Projects/progbase3/src/cascades/face_lbp.xml",
            "/home/zulus/Projects/progbase3/src/cascades/eye_haar.xml");
    VideoCapture capture;
    capture.open(0);
    if (detector->isLoaded(EYES_HAAR) && detector->isLoaded(FACE_HAAR) && detector->isLoaded(FACE_LBP)) {
//        Mat cap_frame;
//        while (capture.read(cap_frame)) {
            FImage *image = new FImage("/home/zulus/Projects/progbase3/res/people.jpg");
//            FImage *image = new FImage(cap_frame);
            detector->detect_faces(*image);
            Mat frame = image->get_image().clone();
            auto faces = image->get_faces();
            cout << faces.size() << endl;
            for (int i = 0; i < faces.size(); i++) {
                Mat m_face = faces[i]->get_image().clone();
                circle(m_face, faces[i]->get_person()->get_eye_left().pos,
                       faces[i]->get_person()->get_eye_left().radius,
                       Scalar(255, 255, 0));
                circle(m_face, faces[i]->get_person()->get_eye_rigth().pos,
                       faces[i]->get_person()->get_eye_rigth().radius,
                       Scalar(45, 45, 200));
                imshow(to_string(i), m_face);
                rectangle(frame, faces[i]->get_frame(), Scalar(255, 0, 0));
                m_face.release();
            }

            imshow("original", frame);
            delete image;
            frame.release();
//            cap_frame.release();
            char c = (char) waitKey(0);
//            if (c == 27) break;
//        }
    }
    delete detector;
    return EXIT_SUCCESS;
}
