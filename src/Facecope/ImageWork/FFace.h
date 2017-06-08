#ifndef FPERSON_H
#define FPERSON_H
#include <FacecopeTypes.h>
#include <opencv2/imgproc.hpp>

class FFace {
  int rotation;
  cv::Rect face_frame;
  cv::Rect original_frame;

  long face_area_id;
  Eye eye_left;
  Eye eye_rigth;

  Human info;

  bool is_normalized;

private:
  void set_face_frame(const cv::Rect &frame);
  void set_info() const;
  void normalize();

public:
  FFace(const cv::Rect &face_area_frame, const cv::Rect &eye_1,
        const cv::Rect &eye_2, long ID = -1);
  ~FFace();

  int get_rotation() const;
  cv::Rect &get_face_frame() const;
  cv::Rect &get_original_frame() const;
  long get_ID() const;
  Human &get_info() const;
  Eye &get_left_eye() const;
  Eye &get_rigth_eye() const;

  void set_rotation(int angle);
  void set_original_frame(const cv::Rect &frame) const;
  void set_ID(long ID) const;
  void set_left_eye(const cv::Rect &frame_eye) const;
  void set_rigth_eye(const cv::Rect &frame_eye) const;
};

#endif // FPERSON_H
