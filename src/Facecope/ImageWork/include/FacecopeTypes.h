#ifndef FACECOPETYPES_H
#define FACECOPETYPES_H
#include <QString>
#include <opencv2/imgproc.hpp>
enum { MALE = 0xC, FEMALE, UNRECOGNIZED } Sex;

class FFace;
class FImage;
class FFaceDetector;
class FFaceRecognizer;
typedef struct {
  FFaceDetector *detector;
  FFaceRecognizer *recognizer_face;
  FFaceRecognizer *recognizer_gender;
} FacecopeProcessors;

typedef struct {
  cv::Point pos;
  int radius;
} Eye;

typedef struct {
  long ID;
  int gender;
  FFace *face;
  QString name;
} Human;

#endif // FACECOPETYPES_H
