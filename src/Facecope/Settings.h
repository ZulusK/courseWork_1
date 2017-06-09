#ifndef SETTINGS_H
#define SETTINGS_H
#include <QJsonObject>
#include <QString>
enum { USE_HAAR = 13, USE_LBP };
#define THREAHOLD "threahold"
#define OUT_DIR "out_dir"
#define SKIP_UR "skip_unrecognized"
#define LEARN_GENDER "learn_gender"
#define LEARN_RECOGNIZED "learn_recognized"
#define STEPS_DETECTION "steps_of_detection"
#define CASCADE_TYPE "use_cascade"
#define EXPORT_DIR "export_dir"
#define DATABASE_PATH "database_path"
#define EXPORT_SETTINGS_FILE_NAME "settings.fcp"

class Settings {
public:
  Settings(const QString &settingsPath = QString());
  ~Settings();

  QString getOutput_dir() const;
  void setOutput_dir(const QString &value);

  double getThreahold() const;
  void setThreahold(double value);

  bool getSkip_recognized() const;
  void setSkip_unRecognized(bool value);

  bool getCut_files() const;
  void setCut_files(bool value);

  bool getLearn_gender() const;
  void setLearn_gender(bool value);

  bool getLearn_recognized() const;
  void setLearn_recognized(bool value);

  int getSteps_of_detection() const;
  void setSteps_of_detection(int value);

  int getCascade_type() const;
  void setCascade_type(int value);

  QString getExport_path() const;
  void setExport_path(const QString &value);

  QString getDatabase_path() const;
  void setDatabase_path(const QString &value);

  QString getGender_database_path() const;

  QString getSave_settings_path() const;

  void load(const QString &path);
  void save(const QString &path = QString());

  void useDefault();

private:
  void setOutput_dir(const QJsonObject &jobj);
  void setThreahold(const QJsonObject &jobj);
  void setSkip_unRecognized(const QJsonObject &jobj);
  void setCut_files(const QJsonObject &jobj);
  void setLearn_gender(const QJsonObject &jobj);
  void setLearn_recognized(const QJsonObject &jobj);
  void setSteps_of_detection(const QJsonObject &jobj);
  void setCascade_type(const QJsonObject &jobj);
  void setExport_path(const QJsonObject &jobj);
  void setDatabase_path(const QJsonObject &jobj);

  QString output_dir;
  QString export_path;
  QString database_path;
  QString gender_database_path;
  QString save_settings_path;
  bool skip_unRecognized;
  bool cut_files;
  bool learn_gender;
  bool learn_recognized;
  int steps_of_detection;
  int cascade_type;
  double threahold;
};

#endif // SETTINGS_H
