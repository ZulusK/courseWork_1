//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_PERSONDETECTOR_H
#define FISHERFACE_PERSONDETECTOR_H

#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>
#include <map>
#include <Facecope.h>

#define FACE_CASCADE_NAME "haarcascade_frontalface_default.xml"
#define EYE_CASCADE_NAME "haarcascade_eye.xml"

class facecope::FaceDetector {
    // map with all loaded cascades
    std::map<int, cv::CascadeClassifier *> cascades;
    //minimum possible object size. Objects smaller than that are ignored.
    cv::Size def_face_min;
    float def_eye_min;

    //maximum possible object size. Objects bigger than that are ignored.
    cv::Size def_face_max;
    float def_eye_max;

    //angle increment of each iteration of rotation image
    float def_rotate_step;

    //scale factor
    double def_scaleFactor;
private:

    /**
     * @brief detects objects at image using clessifier
     * @param classifier ref. to cascade classifier
     * @param grayImage ref. to grayscaled image (eq. 1 channel)
     * @param rects ref. to vector, that will contain bounds of detected objects
     * @param scaleFactor scale factor
     * @param minSize minimum possible object size. Objects smaller than that are ignored.
     * @param maxSize maximum possible object size. Objects bigger than that are ignored.
     */
    void detectObject(cv::CascadeClassifier &classifier,
                      const cv::Mat &grayImage,
                      std::vector<cv::Rect> &rects,
                      double scaleFactor,
                      cv::Size minSize,
                      cv::Size maxSize);

    /**
     * @brief remove rectangles, that don't contains face
     * @param grayImage ref. to gray-scaled image
     * @param rects ref. to vector, that contains all bounding rectangles
     * @param eyes ref. to vector, that contains all bounding rectangles, that contains eyes
     */
    void remove_artifactedFaces(cv::Mat &grayImage, std::vector<cv::Rect> &rects, std::vector<cv::Rect[2]> eyes);

public:
    /**
    * @brief constructor of FaceDetector, load cascade from xml-file
    * @param cascadeFolderPath path to directory with Haar's cascades
    */
    FaceDetector(const std::string &cascadeFolderPath);

    /**
     * @brief  destructor
     */
    ~FaceDetector();

    /**
     * @brief finds faces in the image and returns the rectangles that surround them.
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     */
    void detectFace(const cv::Mat &originalImage, std::vector<cv::Rect> rects);

    /**
    * @brief finds eyes in the image and returns the rectangles that surround them.
    * @param image reference to image to process
    * @param eyes reference to vector for storing the found framing rectangles
    */
    void detectEye(const cv::Mat &originalImage, std::vector<cv::Rect> eyes);


    /**
    * @brief check, is cascade classifier for face loaded
    * @return true, if loaded, else - false
    */
    bool isLoaded_face();

    /**
     * @brief check, is cascade classifier for eyes loaded
     * @return true, if loaded, else - false
     */
    bool isLoaded_eye();

    /**
     *
     * @param image
     * @param rects reference to vector for storing the found framing rectangles
     * @param detectAllDegreese find faces at all possible angles of rotation
     * @param persons reference to vector for storing the found persons
     * @param normalized should face be normalized (eq. rotated)
     */
    /**
     * @brief get found faces framed by rectangles from image
     * @param originalImage reference to image to process
     * @param persons reference to map of all detected persons
     * @param allAngles Find faces in the image for all possible angles of rotation. The step of increasing the angle of rotation is given by def_rotate_step
     */
    void detect_PersonFace(const cv::Mat &originalImage, std::map<long, facecope::Face> persons, bool allAngles);


    const cv::Size &getDef_face_min() const;

    void setDef_face_min(const cv::Size &def_face_min);

    const cv::Size &getDef_face_max() const;

    void setDef_face_max(const cv::Size &def_face_max);

    float getDef_eye_min() const;

    void setDef_eye_min(float def_eye_min);

    float getDef_eye_max() const;

    void setDef_eye_max(float def_eye_max);

    float getDef_smile_min() const;

    void setDef_smile_min(float def_smile_min);

    float getDef_smile_max() const;

    void setDef_smile_max(float def_smile_max);

    double getDef_scaleFactor() const;

    void setDef_scaleFactor(double def_scaleFactor);

    float getDef_rotate_step() const;

    void setDef_rotate_step(float def_rotate_step);
};


#endif //FISHERFACE_PERSONDETECTOR_H
