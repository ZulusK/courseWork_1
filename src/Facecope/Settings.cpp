#include "Settings.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
Settings::Settings() {
  useDefault();
  load(DEFAULT_SETTINGS_PATH EXPORT_SETTINGS_FILE_NAME);
}
Settings::~Settings() { save(DEFAULT_SETTINGS_PATH); }

void Settings::useDefault() {
  _output_path = DEFAULT_OUTPUT_PATH;
  _skip_unRecognized = true;
  _cut_files = true;
  _learn_gender = true;
  _learn_recognized = true;
  _steps_of_detection = 1;
  _cascade_type = USE_HAAR;
  _threahold = 1000;
}

QString Settings::getOutput_path() const { return _output_path; }

void Settings::setOutput_path(const QString &output_path) {
  if (QDir(output_path).exists())
    _output_path = output_path;
}

bool Settings::getSkip_unRecognized() const { return _skip_unRecognized; }

void Settings::setSkip_unRecognized(bool skip_unRecognized) {
  _skip_unRecognized = skip_unRecognized;
}

bool Settings::getCut_files() const { return _cut_files; }

void Settings::setCut_files(bool cut_files) { _cut_files = cut_files; }

bool Settings::getLearn_gender() const { return _learn_gender; }

void Settings::setLearn_gender(bool learn_gender) {
  _learn_gender = learn_gender;
}

bool Settings::getLearn_recognized() const { return _learn_recognized; }

void Settings::setLearn_recognized(bool learn_recognized) {
  _learn_recognized = learn_recognized;
}

int Settings::getSteps_of_detection() const { return _steps_of_detection; }

void Settings::setSteps_of_detection(int steps_of_detection) {
  if (steps_of_detection > 0)
    _steps_of_detection = steps_of_detection;
}

int Settings::getCascade_type() const { return _cascade_type; }

void Settings::setCascade_type(int cascade_type) {
  _cascade_type = cascade_type;
}

double Settings::getThreahold() const { return _threahold; }

void Settings::setThreahold(double threahold) { _threahold = threahold; }

QString readJSON(const QString &filePath) {
  QFile file(filePath);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    return "";
  } else {
    QString s = QTextStream(&file).readAll();
    file.close();
    return s;
  }
}

void Settings::load(const QString &path) {
  // todo
  qDebug() << "load settings" << path;
  QString text = readJSON(path);
  if (text.length() != 0) {
    QJsonDocument jdoc = QJsonDocument::fromJson(text.toUtf8());
    if (jdoc.isObject()) {
      auto jobj = jdoc.object();
      loadOutput_path(jobj);
      loadThreahold(jobj);
      loadSkip_unRecognized(jobj);
      loadCut_files(jobj);
      loadLearn_gender(jobj);
      loadLearn_recognized(jobj);
      loadSteps_of_detection(jobj);
      loadCascade_type(jobj);
      qDebug() << "settings has been loaded";
    }
  }
}

void Settings::loadOutput_path(const QJsonObject &jobj) {
  if (jobj.contains(OUT_PATH)) {
    setOutput_path(jobj[OUT_PATH].toString());
  }
}

void Settings::loadThreahold(const QJsonObject &jobj) {
  if (jobj.contains(THREAHOLD)) {
    setThreahold(jobj[THREAHOLD].toDouble());
  }
}

void Settings::loadSkip_unRecognized(const QJsonObject &jobj) {
  if (jobj.contains(SKIP_UR)) {
    setSkip_unRecognized(jobj[SKIP_UR].toBool());
  }
}

void Settings::loadCut_files(const QJsonObject &jobj) {
  if (jobj.contains(CUT_FILES)) {
    setCut_files(jobj[CUT_FILES].toBool());
  }
}

void Settings::loadLearn_gender(const QJsonObject &jobj) {
  if (jobj.contains(LEARN_GENDER)) {
    setLearn_gender(jobj[LEARN_GENDER].toBool());
  }
}

void Settings::loadLearn_recognized(const QJsonObject &jobj) {
  if (jobj.contains(LEARN_RECOGNIZED)) {
    setLearn_recognized(jobj[LEARN_RECOGNIZED].toBool());
  }
}

void Settings::loadSteps_of_detection(const QJsonObject &jobj) {
  if (jobj.contains(STEPS_DETECTION)) {
    setSteps_of_detection(jobj[STEPS_DETECTION].toInt());
  }
}

void Settings::loadCascade_type(const QJsonObject &jobj) {
  if (jobj.contains(CASCADE_TYPE)) {
    if (jobj[CASCADE_TYPE].toString().compare("LBP") == 0) {
      setCascade_type(USE_LBP);
    } else {
      setCascade_type(USE_HAAR);
    }
  }
}

void Settings::save(const QString &dir_path) {
  // todo
  QString path = dir_path + EXPORT_SETTINGS_FILE_NAME;

  qDebug() << "save settings to " << path;
  QJsonObject jobj;
  jobj[QString(THREAHOLD)] = _threahold;
  jobj[QString(OUT_PATH)] = _output_path;
  jobj[QString(SKIP_UR)] = _skip_unRecognized;
  jobj[QString(CUT_FILES)] = _cut_files;
  jobj[QString(LEARN_GENDER)] = _learn_gender;
  jobj[QString(LEARN_RECOGNIZED)] = _learn_recognized;
  jobj[QString(CASCADE_TYPE)] = (_cascade_type == USE_LBP) ? "LBP" : "HAAR";
  jobj[QString(STEPS_DETECTION)] = _steps_of_detection;
  QJsonDocument jdoc(jobj);
  QFile jfile(path);
  jfile.open(QFile::WriteOnly);
  if (jfile.isOpen()) {
    jfile.write(jdoc.toJson());
    jfile.close();
    qDebug() << "settings has been saved to " << path;
  }
}

QString Settings::getSave_settings_path() const {
  return DEFAULT_SETTINGS_PATH EXPORT_SETTINGS_FILE_NAME;
}
QString Settings::getDatabase_path() const { return DEAFULT_DATABASE_PATH; }

QString Settings::getRecognizer_gender_path() const {
  return DEFAULT_RECOGNIZER_GENDER_PATH;
}
QString Settings::getRecognizer_path() const { return DEFAULT_RECOGNIZER_PATH; }
