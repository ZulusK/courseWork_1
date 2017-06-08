#ifndef FACECOPETYPES_H
#define FACECOPETYPES_H
#include <opencv2/imgproc.hpp>

enum { MAN = 0xC, WOMAN, UNRECOGNIZED } Sex;

class FFace;
class FImage;
class FFaceDetector;
class FFaceRecognizer;
typedef struct {
  FFaceDetector *detector;
  FFaceRecognizer *recognizer;
} FacecopeProcessors;

typedef struct {
  cv::Point pos;
  int radius;
} Eye;
typedef struct {
  long ID;
  int sex;
  FFace *face;
} Human;

#endif // FACECOPETYPES_H
