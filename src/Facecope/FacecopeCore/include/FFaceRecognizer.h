/** @file
    @brief The class recognizer - the face recognizing on the photo
*/

#ifndef FFACERECOGNIZER_H
#define FFACERECOGNIZER_H
#include <FacecopeTypes.h>
#include <map>
#include <opencv2/face.hpp>

class FFaceRecognizer {
  cv::Ptr<cv::face::BasicFaceRecognizer> recognizer;
  cv::Size imageScaleSize;

private:
public:
  FFaceRecognizer(const std::string &dirPath,
                  const cv::Size &sizeOfImage = cv::Size(150, 150),
                  int numOfComponents = 80, double threahold = DBL_MAX);

  FFaceRecognizer(const cv::Size &imageScaleSize = cv::Size(150, 150));

  ~FFaceRecognizer();

  int recognize(const cv::Mat &face);

  bool load(const std::string &loadPath);

  bool save(const std::string &savePath);

  void set_threahold(double threahold);

  double get_threahold();

  int get_num_of_components();

  void set_num_of_components(int number);

  bool learn(const std::vector<cv::Mat> &images, const std::vector<int> labels);
  cv::Size get_size_of_image();
};

#endif // FFACERECOGNIZER_H
