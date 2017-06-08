#ifndef FACECOPETYPES_H
#define FACECOPETYPES_H
#include <opencv2/imgproc.hpp>

enum { MAN = 0xC, WOMAN,UNRECOGNIZED } Sex;

class FFace;
class FImage;

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
