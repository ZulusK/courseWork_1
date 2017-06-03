//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_PERSONFACE_H
#define FISHERFACE_PERSONFACE_H

#include <vector>
#include <opencv2/imgproc.hpp>

/**
 * @brief defines class, that contains person's face
 */
class PersonFace {
private:
    cv::Mat faceRGB;
    cv::Mat faceGray;
    cv::Rect eyes[2];
    cv::Rect smile;
    long id;


public:

    PersonFace(const cv::Mat &faceRGB, const cv::Mat &faceGray, long id = 0);

    PersonFace(const cv::Mat &faceRGB, long id = 0);

    ~PersonFace();

    long getId() const;

    void setId(long id);

    void setEyes(cv::Rect &left, cv::Rect &rect);

    void setSmile(const cv::Rect &smile);

    const cv::Mat &getFaceRGB() const;

    const cv::Mat &getFaceGray() const;

    const cv::Rect *getEyes() const;

    const cv::Rect &getSmile() const;

    void setFaceRGB(const cv::Mat &faceRGB);

};


#endif //FISHERFACE_PERSONFACE_H
