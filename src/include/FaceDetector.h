//
// Created by Danil Kazimirov on 05.06.17.
//
#ifndef FACECOPE_DETECTOR_H
#define FACECOPE_DETECTOR_H

#include <Facecope.h>
#include <opencv2/objdetect.hpp>
#include <map>
#include <vector>

#define FACE_CASCADE_NAME "haarcascade_frontalface_default.xml"
#define EYE_CASCADE_NAME "haarcascade_eye.xml"

class FaceDetector {
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
     * @param allEyes ref. to vector, that contains all bounding rectangles, that contains eyes
     */
    void remove_artifactedFaces(cv::Mat &grayImage, std::vector<cv::Rect> &rects,
                                std::vector<std::vector<cv::Rect>> &allEyes);

    /**
     * @brief find persons at image, and remove them from image (fill rect. black color), use for detec person on all angles
     * @param imageGray ref. to grayscaled image
     * @param imageRGB ref. to rgb image
     * @param persons ref. to list of find people
     * @param angle angle of current rotation
     * @param centerOfRotation center of image rotatin
     */
    void find_PersonsFaces(cv::Mat &imageGray, const cv::Mat &imageRGB, std::map<long, Face> &persons, float angle,cv::Point2f & centerOfRotation);

    /**
     * @brief find persons at image
     * @param imageRGB ref. to rgb image
     * @param persons ref. to list of find people
     */
    void find_PersonsFaces(const cv::Mat &imageRGB, std::map<long, Face> &persons);

    /**
     *
     * @param imageRGB
     * @param frameRect
     * @param eyes
     * @return
     */
    PersonFace *createPersonFace(const cv::Mat imageRGB, cv::Rect &frameRect, std::vector<cv::Rect> &eyes);

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
    void detectFace(const cv::Mat &originalImage, std::vector<cv::Rect> rects,
                                  std::vector<std::vector<cv::Rect>> &eyes);

    /**
    * @brief finds eyes in the image and returns the rectangles that surround them.
    * @param image reference to image to process
    * @param eyes reference to vector for storing the found framing rectangles
    */
    void detectEye(const cv::Mat &originalImage, std::vector<cv::Rect> &eyes);

    /**
     * @brief get found faces framed by rectangles from image
     * @param originalImage reference to image to process
     * @param persons reference to map of all detected persons
     * @param allAngles Find faces in the image for all possible angles of rotation. The step of increasing the angle of rotation is given by def_rotate_step
     */
    void detect_PersonFace(const cv::Mat &originalImage, std::map<long, Face> &persons, bool allAngles);


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


#endif //FACECOPE_DETECTOR_H
