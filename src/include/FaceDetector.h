//
// Created by Danil Kazimirov on 02.06.17.
//

#ifndef FISHERFACE_FACEDETECTOR_H
#define FISHERFACE_FACEDETECTOR_H

#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>
#include <map>
#include <PersonFace.h>

#define FACE_CASCADE_NAME "haarcascade_frontalface_default.xml"
#define EYE_CASCADE_NAME "haarcascade_eye.xml"
#define SMILE_CASCADE_NAME "haarcascade_smile.xml"

/**
 * @brief defines face detector-class
 */
class FaceDetector {
private:
    std::map<int, cv::CascadeClassifier *> cascades;
    float def_faceScale_min;
    float def_eyeScale_min;
    float def_mouthScale_min;

    float def_faceScale_max;
    float def_eyeScale_max;
    float def_mouthScale_max;

    double def_scaleFactor = 1.1;


    void findObject(cv::CascadeClassifier &clasifier,
                    const cv::Mat &grayImage,
                    std::vector<cv::Rect> &rects,
                    double scaleFactor,
                    cv::Size minSize,
                    cv::Size maxSize);

    cv::Mat normalizeFace(cv::Mat &image);

    cv::Mat cutFace();

public:
    /**
     * @brief constructor of FaceDetector, load cascade from xml-file
     * @param cascadeFolderPath path to directory with Haar's cascades
     */
    FaceDetector(const std::string &cascadeFolderPath);

    /**
     * @brief default destuctor
     */
    ~FaceDetector();

    /**
     * @brief finds the faces in the image and returns the rectangles that surround them.
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param removeArtifacts  remove area without faces (uses extra calculating)
     * @param scaleFactor specifying how much the image size is reduced at each image scale.
     * @param minSize minimum possible object size. Objects smaller than that are ignored.
     * @param maxSize maximum possible object size. Objects bigger than that are ignored.
     */
    void detectFaces(const cv::Mat &image, std::vector<cv::Rect> &rects, bool removeArtifacts, double scaleFactor = 1.1,
                     float face);

    /**
     * @brief finds eyes in the image and returns the rectangles that surround them.
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param scaleFactor specifying how much the image size is reduced at each image scale.
     * @param minSize minimum possible object size. Objects smaller than that are ignored.
     * @param maxSize maximum possible object size. Objects bigger than that are ignored.
     */
    void detectEyes(const cv::Mat &image, std::vector<cv::Rect> &rects, double scaleFactor = 1.1,
                    cv::Size minSize = cv::Size(),
                    cv::Size maxSize = cv::Size());

    /**
     * @brief finds smiles in the image and returns the rectangles that surround them.
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param scaleFactor specifying how much the image size is reduced at each image scale.
     * @param minSize minimum possible object size. Objects smaller than that are ignored.
     * @param maxSize maximum possible object size. Objects bigger than that are ignored.
     */
    void detectSmile(const cv::Mat &image, std::vector<cv::Rect> &rects, double scaleFactor = 1.1,
                     cv::Size minSize = cv::Size(),
                     cv::Size maxSize = cv::Size());

    /**
     * @brief get found faces framed by rectangles from image
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param faces reference to vector for storing the found faces
     * @param toGray convert faces to grayscale
     * @param normalized should face be normalized (eq. rotated)
     */
    void getFaces(const cv::Mat &image, std::vector<cv::Rect> &rects, std::vector<cv::Mat> &faces, bool toGray = false,
                  bool normalized = false);

    /**
     * @brief get found faces framed by rectangles from image
     * @param image reference to image to process
     * @param faces reference to vector for storing the found faces
     * @param toGray convert faces to grayscale
     * @param normalized should face be normalized (eq. rotated)
     */
    void getFaces(const cv::Mat &image, std::vector<cv::Mat> &faces, bool toGray = false, bool normalized = false);

    /**
     * @brief get found faces framed by rectangles from image
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param persons reference to vector for storing the found persons
     * @param normalized should face be normalized (eq. rotated)
     */
    void getFaces(const cv::Mat &image, std::vector<cv::Rect> &rects, std::vector<PersonFace *> &persons,
                  bool normalized = false);

    /**
     * @brief get face framed by rectangle from image
     * @param image reference to image to process
     * @param rect reference to framing rectangle
     * @param normalized should face be normalized (eq. rotated)
     * @return face framed by rectangle from image
     */
    cv::Mat getFace(const cv::Mat &image, const cv::Rect &rect, bool normalized);


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
     * @brief check, is cascade classifier for smile loaded
     * @return true, if loaded, else - false
     */
    bool isLoaded_smile();


    float getDef_faceScale_min() const;

    void setDef_faceScale_min(float def_faceScale_min);

    float getDef_eyeScale_min() const;

    void setDef_eyeScale_min(float def_eyeScale_min);

    float getDef_mouthScale_min() const;

    void setDef_mouthScale_min(float def_mouthScale_min);

    float getDef_faceScale_max() const;

    void setDef_faceScale_max(float def_faceScale_max);

    float getDef_eyeScale_max() const;

    void setDef_eyeScale_max(float def_eyeScale_max);

    float getDef_mouthScale_max() const;

    void setDef_mouthScale_max(float def_mouthScale_max);

    double getDef_scaleFactor() const;

    void setDef_scaleFactor(double def_scaleFactor);
};


#endif //FISHERFACE_FACEDETECTOR_H
