#ifndef FIMAGE_H
#define FIMAGE_H
#include <FFace.h>
#include <FacecopeTypes.h>
#include <QImage>
#include <QString>
#include <QVector>
#include <opencv2/imgproc.hpp>
#include <vector>

class FImage {
  QVector<FFace *> faces;
  QImage q_image;
  cv::Mat cv_image;
  bool is_detected;
  bool is_recognized;
  QString name;

public:
  FImage(const QString &path);

  FImage(const cv::Mat &mat);

  ~FImage();

  QString get_name() const;

  void set_name(const QString &name);

  QImage to_q_image();

  cv::Mat to_cv_image();

  void set_recognized(bool recognized);

  void set_detected(bool detected);

  int add_face(FFace *face);

  void add_faces(std::vector<FFace *> &faces);

  FFace *remove_face(long ID);

  QVector<FFace *> &get_faces();

  FFace *get_face(long ID);

  void clear();

  bool empty() const;

  cv::Size cv_size() const;

  QSize q_size() const;

  cv::Mat get_face_cv_image(FFace *face);
  QRect get_face_q_frame(FFace * face);
};

#endif // FIMAGE_H
