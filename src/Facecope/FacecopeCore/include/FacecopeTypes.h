/** @file
    @brief defines core functional of Facecope
*/
#ifndef FACECOPETYPES_H
#define FACECOPETYPES_H
#include <QString>
#include <opencv2/imgproc.hpp>
enum { MALE = 1, FEMALE = 2, UNRECOGNIZED = -1 } Sex;

class FFace;
class FImage;
class FFaceDetector;
class FFaceRecognizer;
class Settings;
class FDatabaseDriver;
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

typedef struct {
  FFaceDetector *detector;
  FFaceRecognizer *recognizer_face;
  FFaceRecognizer *recognizer_gender;
  FDatabaseDriver *database;
  Settings *settings;
} Facecope;

void learnNewHuman(Facecope &facecope, int ID, int gender);
#endif // FACECOPETYPES_H
