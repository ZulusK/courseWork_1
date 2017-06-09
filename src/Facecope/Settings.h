#ifndef SETTINGS_H
#define SETTINGS_H
#include <QJsonObject>
#include <QString>
enum { USE_HAAR = 13, USE_LBP };
// name of fields
#define THREAHOLD "threahold"
#define CUT_FILES "cut files"
#define OUT_PATH "out dir"
#define SKIP_UR "skip unrecognized"
#define LEARN_GENDER "learn gender"
#define LEARN_RECOGNIZED "learn recognized"
#define STEPS_DETECTION "steps of detection"
#define CASCADE_TYPE "use cascade"
#define EXPORT_DIR "export dir"

// paths
#define EXPORT_SETTINGS_FILE_NAME "settings.fcp"
#define DEAFULT_DATABASE_PATH "../../res/facecope.db"
#define DEFAULT_RECOGNIZER_PATH "../../res/faces.xml"
#define DEFAULT_RECOGNIZER_GENDER_PATH "../../res/genders_recognition.xml"
#define DEFAULT_SETTINGS_PATH "../../res/"
#define DEFAULT_FACES_PATH "../../faces/"
#define DEFAULT_OUTPUT_PATH "~/"
class Settings {
public:
  Settings();
  ~Settings();

  QString getDatabase_path() const;
  QString getFacesPrev_path() const;
  QString getRecognizer_path() const;
  QString getRecognizer_gender_path() const;
  QString getSave_settings_path() const;

  void load(const QString &path);
  void save(const QString &path = QString());
  void useDefault();

  QString getOutput_path() const;
  void setOutput_path(const QString &output_path);

  bool getSkip_unRecognized() const;

  void setSkip_unRecognized(bool skip_unRecognized);

  bool getCut_files() const;
  void setCut_files(bool cut_files);

  bool getLearn_gender() const;
  void setLearn_gender(bool learn_gender);

  bool getLearn_recognized() const;
  void setLearn_recognized(bool learn_recognized);

  int getSteps_of_detection() const;
  void setSteps_of_detection(int steps_of_detection);

  int getCascade_type() const;
  void setCascade_type(int cascade_type);

  double getThreahold() const;
  void setThreahold(double threahold);

private:
  void loadOutput_path(const QJsonObject &jobj);
  void loadThreahold(const QJsonObject &jobj);
  void loadSkip_unRecognized(const QJsonObject &jobj);
  void loadCut_files(const QJsonObject &jobj);
  void loadLearn_gender(const QJsonObject &jobj);
  void loadLearn_recognized(const QJsonObject &jobj);
  void loadSteps_of_detection(const QJsonObject &jobj);
  void loadCascade_type(const QJsonObject &jobj);

  QString _output_path;
  bool _skip_unRecognized;
  bool _cut_files;
  bool _learn_gender;
  bool _learn_recognized;
  int _steps_of_detection;
  int _cascade_type;
  double _threahold;
};

#endif // SETTINGS_H
