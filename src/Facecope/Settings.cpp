#include "Settings.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
Settings::Settings(const QString &settingsPath) {
  useDefaultSettings();
  if (QFile(settingsPath).exists()) {
    this->save_settings_path = settingsPath;
  } else {
    this->save_settings_path = export_path;
  }
  load(save_settings_path+EXPORT_SETTINGS_FILE_NAME);
}
Settings::~Settings() { save(save_settings_path); }

QString Settings::getOutput_dir() const { return output_dir; }

void Settings::useDefault(){
    this->output_dir = "~/Facecope/";
    this->gender_database_path = "./";
    this->export_path = "./";
    this->cut_files = false;
    this->threahold = 1000;
    this->steps_of_detection = 1;
    this->skip_unRecognized = true;
    this->learn_recognized = true;
    this->learn_gender = true;
    this->cascade_type = USE_HAAR;
}

void Settings::setOutput_dir(const QString &value) {
  qDebug() << "output dir changed" << value;
  if (QDir(value).exists())
    output_dir = value;
}

double Settings::getThreahold() const { return threahold; }

void Settings::setThreahold(double value) {
  qDebug() << "threahold changed" << value;
  if (threahold > 0)
    threahold = value;
}

bool Settings::getSkip_recognized() const { return skip_unRecognized; }

void Settings::setSkip_unRecognized(bool value) {
  qDebug() << "skip recognized changed" << value;
  skip_unRecognized = value;
}

bool Settings::getCut_files() const { return cut_files; }

void Settings::setCut_files(bool value) {
  qDebug() << "cut file changed" << value;
  cut_files = value;
}

bool Settings::getLearn_gender() const { return learn_gender; }

void Settings::setLearn_gender(bool value) {
  qDebug() << "learn gender changed" << value;
  learn_gender = value;
}

bool Settings::getLearn_recognized() const { return learn_recognized; }

void Settings::setLearn_recognized(bool value) {
  qDebug() << "lear recognized changed" << value;
  learn_recognized = value;
}

int Settings::getSteps_of_detection() const { return steps_of_detection; }

void Settings::setSteps_of_detection(int value) {
  qDebug() << "step of detect changed" << value;
  if (value > 0)
    steps_of_detection = value;
}

int Settings::getCascade_type() const { return cascade_type; }

void Settings::setCascade_type(int value) {
  qDebug() << "cascade type changed" << value;
  cascade_type = value;
}

QString Settings::getExport_path() const { return export_path; }

void Settings::setExport_path(const QString &value) {
  qDebug() << "export path changed" << value;
  if (QDir(value).exists())
    export_path = value;
}

QString Settings::getDatabase_path() const { return database_path; }

void Settings::setDatabase_path(const QString &value) {
  qDebug() << "database changed" << value;
  if (QFile(value).exists())
    database_path = value;
}

QString Settings::getGender_database_path() const {
  return gender_database_path;
}
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

void Settings::setOutput_dir(const QJsonObject &jobj) {
  if (!jobj[QString(OUT_DIR)].isNull()) {
    setOutput_dir(this->output_dir = jobj[QString(OUT_DIR)].toString());
  }
}

void Settings::setThreahold(const QJsonObject &jobj) {
  if (!jobj[QString(THREAHOLD)].isNull()) {
    setThreahold(jobj[QString(THREAHOLD)].toDouble());
  }
}

void Settings::setSkip_unRecognized(const QJsonObject &jobj) {
  if (!jobj[QString(SKIP_UR)].isNull()) {
    setSkip_unRecognized(jobj[QString(SKIP_UR)].toBool());
  }
}

void Settings::setCut_files(const QJsonObject &jobj) {
  if (!jobj[QString(SKIP_UR)].isNull()) {
    setSkip_unRecognized(jobj[QString(SKIP_UR)].toBool());
  }
}

void Settings::setLearn_gender(const QJsonObject &jobj) {
  if (!jobj[QString(LEARN_GENDER)].isNull()) {
    setLearn_gender(jobj[QString(LEARN_GENDER)].toBool());
  }
}

void Settings::setLearn_recognized(const QJsonObject &jobj) {
  if (!jobj[QString(LEARN_RECOGNIZED)].isNull()) {
    setLearn_recognized(jobj[QString(LEARN_RECOGNIZED)].toBool());
  }
}

void Settings::setSteps_of_detection(const QJsonObject &jobj) {
  if (!jobj[QString(STEPS_DETECTION)].isNull()) {
    setSteps_of_detection(jobj[QString(STEPS_DETECTION)].toInt());
  }
}

void Settings::setCascade_type(const QJsonObject &jobj) {
  if (!jobj[QString(CASCADE_TYPE)].isNull()) {
    if (jobj[QString(CASCADE_TYPE)].toString().compare("LBP") == 0) {
      setCascade_type(USE_LBP);
    } else {
      setCascade_type(USE_HAAR);
    }
  }
}

void Settings::setExport_path(const QJsonObject &jobj) {
  if (!jobj[QString(EXPORT_DIR)].isNull()) {
    setExport_path(jobj[QString(EXPORT_DIR)].toString());
  }
}

void Settings::setDatabase_path(const QJsonObject &jobj) {
  if (!jobj[QString(DATABASE_PATH)].isNull()) {
    setDatabase_path(jobj[QString(DATABASE_PATH)].toString());
  }
}

void Settings::load(const QString &path) {
  // todo
  qDebug() << "load " << path;
  QString text = readJSON(path);
  if (text.length() != 0) {
    QJsonDocument jdoc = QJsonDocument::fromJson(text.toUtf8());
    if (jdoc.isObject()) {
      auto jobj = jdoc.object();
      setOutput_dir(jobj);
      setThreahold(jobj);
      setSkip_unRecognized(jobj);
      setCut_files(jobj);
      setLearn_gender(jobj);
      setLearn_recognized(jobj);
      setSteps_of_detection(jobj);
      setCascade_type(jobj);
      setExport_path(jobj);
      setDatabase_path(jobj);
      qDebug()<<"loaded";
    }
  }
}

void Settings::save(const QString &dir_path) {
  // todo
  QString path = dir_path + EXPORT_SETTINGS_FILE_NAME;

  qDebug() << "save " << path;
  QJsonObject jobj;
  jobj[QString(THREAHOLD)] = threahold;
  jobj[QString(OUT_DIR)] = output_dir;
  jobj[QString(SKIP_UR)] = skip_unRecognized;
  jobj[QString(LEARN_GENDER)] = learn_gender;
  jobj[QString(LEARN_RECOGNIZED)] = LEARN_RECOGNIZED;
  jobj[QString(CASCADE_TYPE)] = (cascade_type == USE_LBP) ? "LBP" : "HAAR";
  jobj[QString(EXPORT_DIR)] = export_path;
  jobj[QString(STEPS_DETECTION)] = steps_of_detection;
  jobj[QString(DATABASE_PATH)] = database_path;
  QJsonDocument jdoc(jobj);
  QFile jfile(path);
  jfile.open(QFile::WriteOnly);
  if (jfile.isOpen()) {
    jfile.write(jdoc.toJson());
    jfile.close();
    qDebug()<<"saved";
  }
}

QString Settings::getSave_settings_path() const { return save_settings_path; }
