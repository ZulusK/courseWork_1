#include "FDatabaseDriver.h"
#include <QDebug>
#include <QFile>
#include <QSqlQuery>
FDatabaseDriver::FDatabaseDriver(Settings &settings) {
  this->settings = &settings;
  if (!connectTo(settings.getDatabase_path())) {
    restoreDataBase();
  }
}
FDatabaseDriver::~FDatabaseDriver() { closeDataBase(); }

QMap<QString, QVariant> FDatabaseDriver::get_user(int id) {
  QMap<QString, QVariant> data;
  QSqlQuery query;
  if (query.exec("SELECT * FROM  recognizedHumans WHERE id=" +
                 QString::number(id))) {
    qDebug() << "get from DB +";
    query.first();
    data[QString("id")] = query.value("id").toInt();
    data[QString("name")] = query.value("name").toString();
    data[QString("gender")] = query.value("gender").toInt();
    data[QString("images")] = query.value("images").toInt();
    data[QString("path")] = query.value("path").toString();
    foreach (auto s, data) { qDebug() << s; }
  } else {
    qDebug() << "get form DB -";
  }
  return data;
}

bool FDatabaseDriver::connectTo(const QString &path) {
  if (!QFile(path).exists()) {
    qDebug() << "can't connect to " << path;
    return false;
  } else if (this->openDataBase(path)) {
    qDebug() << "success opened " << path;
    return true;
  }
}

bool FDatabaseDriver::restoreDataBase() {
  if (this->openDataBase(settings->getDatabase_path())) {
    if (!this->createTable()) {
      return false;
    } else {
      return true;
    }
  } else {
    qDebug() << "Cant restore DB at " << settings->getDatabase_path();
    return false;
  }
}

bool FDatabaseDriver::openDataBase(const QString &path) {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setHostName("FACECOPE");
  db.setDatabaseName(path);
  if (db.open()) {
    qDebug() << "database was opened at" << path;
    return true;
  } else {
    qDebug() << "can't open database at" << path;
    return false;
  }
}

bool FDatabaseDriver::set(int id, const QString &key, const QString &value) {
  QSqlQuery query;
  if (query.exec("UPDATE recognizedHumans SET " + key + "='" + value +
                 "' WHERE id=" + QString::number(id))) {
    return true;
  } else {
    return false;
  }
}

int FDatabaseDriver::getNextId() {
  QSqlQuery query;
  if (query.exec("INSERT INTO recognizedHumans (" + value + ")VALUES('" + key +
                 "')")) {
    return true;
  } else {
    return 0;
  }
}

bool FDatabaseDriver::insert(const QString &key, const QString &value) {
  QSqlQuery query;
  if (query.exec("SELECT last_insert_rowid()")) {
    query.first();
    return query.value("last_inserted_rowid()").toString();
  } else {
    return false;
  }
}

QString FDatabaseDriver::get(int id, const QString &key) {
  QSqlQuery query;
  if (query.exec("SELECT " + key +
                 " FROM  recognizedHumans WHERE id=" + QString::number(id))) {
    query.first();
    return query.value(key).toString();
  } else {
    return "";
  }
}

void FDatabaseDriver::closeDataBase() {

  qDebug() << "save data base";
  db.close();
  qDebug() << "saved";
}

bool FDatabaseDriver::createTable() {
  QSqlQuery query;
  if (!query.exec("CREATE TABLE  recognizedHumans"
                  " ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                  "`name` TEXT NOT NULL, `gender` INTEGER DEFAULT -1, `images` "
                  "INTEGER DEFAULT 1, `path` TEXT )")) {
    qDebug() << "Cannot create table";
    return false;
  } else {
    qDebug() << "Table was created";
    return true;
  }
}
