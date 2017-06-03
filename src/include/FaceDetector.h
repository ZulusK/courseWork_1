//
// Created by Danil Kazimirov on 02.06.17.
//

#ifndef FISHERFACE_FACEDETECTOR_H
#define FISHERFACE_FACEDETECTOR_H

#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>
#include <map>


#define FACE_CASCADE_NAME "haarcascade_frontalface_default.xml"
#define EYE_CASCADE_NAME "haarcascade_eye.xml"
#define SMILE_CASCADE_NAME "haarcascade_smile.xml"

/**
 * @brief defines face detector-class
 */
class FaceDetector {
private:
    std::map<int, cv::CascadeClassifier *> cascades;
    cv::Size default_min_size;
    cv::Size default_max_size;
    double default_scale = 1.1;


    void findObject(cv::CascadeClassifier &clasifier,
                    const cv::Mat &grayImage,
                    std::vector<cv::Rect> &rects,
                    double scaleFactor,
                    cv::Size minSize,
                    cv::Size maxSize);

    cv::Mat normalizeFace(cv::Mat & image);

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
     * @param removeArtifacts remove areas, that don't contain faces (uses ext. calculating)
     * @param scaleFactor specifying how much the image size is reduced at each image scale.
     * @param minSize minimum possible object size. Objects smaller than that are ignored.
     * @param maxSize maximum possible object size. Objects bigger than that are ignored.
     */
    void detectFaces(const cv::Mat &image, std::vector<cv::Rect> &rects,bool removeArtifacts, double scaleFactor = 1.1,
                     cv::Size minSize = cv::Size(),
                     cv::Size maxSize = cv::Size());

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

    /**
     *
     * @return current min size of rect for face detection
     */
    const cv::Size &getDefault_min_size() const;

    /**
     * set min rect size for face detection
     * @param default_min_size new value of min size (>1)
     */
    void setDefault_min_size(const cv::Size &default_min_size);

    /**
     *
     * @return current max size of rect for face detection
     */
    const cv::Size &getDefault_max_size() const;

    /**
     * set max rect size for face detection
     * @param default_max_size new value of max size (>1)
     */
    void setDefault_max_size(const cv::Size &default_max_size);

    /**
     *
     * @return current scale factor for face detection
     */
    double getDefault_scale() const;

    /**
     * set scale factor for face detection
     * @param default_scale new value of scale factor (>1)
     */
    void setDefault_scale(double default_scale);
};


#endif //FISHERFACE_FACEDETECTOR_H
