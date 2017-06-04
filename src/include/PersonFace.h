//
// Created by Danil Kazimirov on 03.06.17.
//

#ifndef FISHERFACE_PERSONFACE_H
#define FISHERFACE_PERSONFACE_H

#include <opencv2/imgproc.hpp>
#include <Facecope.h>

#define ROTATE_FACE_MAX_ANGLE 15

/**
 * @brief defines class, that contains person's face
 */
class facecope::PersonFace {
    // face's image
    cv::Mat face_rgb;
    // rects, that are bound of eyes
    cv::Rect eyes[2];
    // id of face
    long id;
    // flag, was face normalized
    bool normalized;
private:
    /**
     * @brief normalize rotation
     */
    void normalize_rotatation();

    /**
     * @brief normalize size (cropp)
     */
    void normalize_size();

public:
    /**
     * @brief constructor
     * @param original ref. to image, that contains face
     * @param eye_1 ref. to first eye
     * @param eye_2 ref. to second eye
     * @param id id of face
     */
    PersonFace(const cv::Mat &original, const cv::Rect &eye_1, const cv::Rect &eye_2, long id = -1);

    /**
     * @brief default destructor
     */
    ~PersonFace();

    /**
     * @brief get id of face( return -1 if not recognized)
     * @return id of face
     */
    long get_id() const;

    /**
     * @brief set id of face
     * @param id new value of face's id
     */
    void set_id(long id);

    /**
     * @brief get ref. to face_rgb
     * @return ref. to face_rgb
     */
    const cv::Mat &get_face_rgb() const;

    /**
     * @brief get eyes
     * @return pointer to array of two eyes ( [0] - left, [1] - right)
     */
    const cv::Rect *get_eyes() const;

    /**
     * @brief check, is image normalized (eq. rotated and cropped)
     * @return true, if normalized, else - false
     */
    bool is_normalized();

    /**
     * @brief normalize face ( rotate and cropp), after this, is_normalized will return true
     */
    void normalize();
};


#endif //FISHERFACE_PERSONFACE_H
