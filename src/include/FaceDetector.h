//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_PERSONDETECTOR_H
#define FISHERFACE_PERSONDETECTOR_H

#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>
#include <map>
#include <PersonFace.h>

#define FACE_CASCADE_NAME "haarcascade_frontalface_default.xml"
#define EYE_CASCADE_NAME "haarcascade_eye.xml"
#define SMILE_CASCADE_NAME "haarcascade_smile.xml"

class FaceDetector {
private:
    std::map<int, cv::CascadeClassifier *> cascades;
    cv::Size def_face_min;
    cv::Size def_face_max;

    float def_eye_min;
    float def_eye_max;

    float def_smile_min;
    float def_smile_max;

    float def_rotate_step;
    double def_scaleFactor;

    /**
     * @brief
     * @param clasifier
     * @param grayImage
     * @param rects
     * @param scaleFactor
     * @param minSize minimum possible object size. Objects smaller than that are ignored.
     * @param maxSize maximum possible object size. Objects bigger than that are ignored.
     */
    void detectObject(cv::CascadeClassifier &clasifier,
                      const cv::Mat &grayImage,
                      std::vector<cv::Rect> &rects,
                      double scaleFactor,
                      cv::Size minSize,
                      cv::Size maxSize);

    /**
     * @brief normalize face by afinne transformation (eq. rotate)
     * @param image ref. to image to process
     * @return normalized face
     */
    cv::Mat normalizeFace(const cv::Mat &image);

    /**
     * @brief normalize face by afinne transformation (eq. rotate)
     * @param image ref. to image to process
     * @param eye_1 ref. to first eye
     * @param eye_2 ref. to second eye
     * @return normalized face
     */
    cv::Mat normalizeFace(const cv::Mat &image, cv::Rect &eye_1, cv::Rect &eye_2);

    /**
     * @brief remove rectangles, that don't contains face
     * @param grayImage ref. to gray-scaled image
     * @param rects ref. to vector, that contains all bounding rectangles
     */
    void removeArtifactsFaces(cv::Mat &grayImage, std::vector<cv::Rect> &rects);

    /**
     * @brief cut image, leave only face, without hair
     * @param image ref. to image to process
     * @param eye_1 ref. to first eye
     * @param eye_2 ref. to second eye
     * @return cutted image
     */
    cv::Mat cutFace(const cv::Mat &image, cv::Rect &eye_1, cv::Rect &eye_2);

    /**
     * @brief get found faces framed by rectangles from image
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param persons reference to vector for storing the found persons
     * @param normalized should face be normalized (eq. rotated)
     */
    void getFaces(cv::Mat &image, std::vector<PersonFace *> &persons,
                  bool normalized);

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
     * @param removeArtifacts  remove area without faces (uses extra calculating)
     */
    void
    detectFace(const cv::Mat &originalImage, std::vector<cv::Rect> rects, bool removeArtifacts);

    /**
    * @brief finds eyes in the image and returns the rectangles that surround them.
    * @param image reference to image to process
    * @param rects reference to vector for storing the found framing rectangles
    */
    void
    detectEye(const cv::Mat &originalImage, std::vector<cv::Rect> rects);

    /**
    * @brief finds smiles in the image and returns the rectangles that surround them.
    * @param image reference to image to process
    * @param rects reference to vector for storing the found framing rectangles
    */
    void
    detectSmile(const cv::Mat &originalImage, std::vector<cv::Rect> rects);

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

    /**
     * @brief get face framed by rectangle from image
     * @param image reference to image to process
     * @param rect reference to framing rectangle
     * @param normalized should face be normalized (eq. rotated)
     * @return face framed by rectangle from image
     */
    cv::Mat getFace(const cv::Mat &image, const cv::Rect &rect, bool normalized = false);

    /**
     * @brief get found faces framed by rectangles from image
     * @param image reference to image to process
     * @param rects reference to vector for storing the found framing rectangles
     * @param detectAllDegreese find faces at all possible angles of rotation
     * @param persons reference to vector for storing the found persons
     * @param normalized should face be normalized (eq. rotated)
     */
    void getFaces(const cv::Mat &image, std::vector<PersonFace *> &persons, bool detectAllDegreese,
                  bool normalized);

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

    const std::map<int, cv::CascadeClassifier *> &getCascades() const;

    void setCascades(const std::map<int, cv::CascadeClassifier *> &cascades);

    float getDef_rotate_step() const;

    void setDef_rotate_step(float def_rotate_step);
};


#endif //FISHERFACE_PERSONDETECTOR_H
