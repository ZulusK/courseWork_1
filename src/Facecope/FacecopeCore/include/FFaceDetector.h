/** @file
    @brief The class declaration - the face detector on the photo
*/


#ifndef FFACEDETECTOR_H
#define FFACEDETECTOR_H
#include <FacecopeTypes.h>
#include <FacecopeUtils.h>
#include <map>
#include <opencv2/objdetect.hpp>
enum { FACE_HAAR = 0xAA, FACE_LBP, EYES_HAAR, HAAR, LBP };
#define CASCADE_FACE_HAAR_PATH                                                 \
  "/usr/local/share/OpenCV/haarcascade_frontalface_default.xml"
#define CASCADE_FACE_LBP_PATH                                                  \
  "/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalcatface.xml"
#define CASCADE_EYES_HAAR_PATH                                                 \
  "/usr/local/share/OpenCV/haarcascade_eye.xml"
class FFaceDetector {
  std::map<int, cv::CascadeClassifier *> classifiers;

public:
private:
  void detect_object(cv::Mat &image_gray, cv::CascadeClassifier &classifier,
                     std::vector<cv::Rect> &rects, float scaleFactor,
                     cv::Size min_size_ratio, cv::Size max_size_ratio);

  void find_faces(cv::Mat &image, std::vector<FFace *> &faces,
                  bool removeFaceWithoutEye, int cascade_type,
                  float scaleFactor, cv::Size min_size_ratio,
                  cv::Size max_size_ratio);

  void find_faces(cv::Mat &image, std::vector<FFace *> &faces,
                  bool removeFaceWithoutEye, int cascade_type, int steps,
                  int range, float scaleFactor, cv::Size min_size_ratio,
                  cv::Size max_size_ratio);

  void get_faces_attr(cv::Mat &image_gray, std::vector<cv::Rect> &bounds,
                      bool removeFaceWithoutEye, std::vector<cv::Rect> &eyes_1,
                      std::vector<cv::Rect> &eyes_2);

  void create_faceAreas(std::vector<FFace *> &faces,
                                std::vector<cv::Rect> &bounds,
                                std::vector<cv::Rect> &eyes_1,
                                std::vector<cv::Rect> &eyes_2, int angle);

public:
  FFaceDetector(
      const std::string &cascadesDir_face_haar = CASCADE_FACE_HAAR_PATH,
      const std::string &cascadesDir_face_lbp = CASCADE_FACE_LBP_PATH,
      const std::string &cascadesDir_eye_haar = CASCADE_EYES_HAAR_PATH);

  ~FFaceDetector();

  void detect_faces(FImage &image, bool removeFaceWithoutEye = false,
                    int cascade_type = HAAR, int steps = 0,
                    int angle_range = 360, double scaleFactor = 1.2,
                    cv::Size min_size_ratio = cv::Size(),
                    cv::Size max_size_ratio = cv::Size());

  void detect_faces(const cv::Mat &image, std::vector<FFace *> &faces,
                    bool removeFaceWithoutEye = false, int cascade_type = HAAR,
                    int steps = 0, int angle_range = 360,
                    double scaleFactor = 1.2,
                    cv::Size min_size_ratio = cv::Size(),
                    cv::Size max_size_ratio = cv::Size());

  bool isLoaded(int what);
};

#endif // FFACEDETECTOR_H
