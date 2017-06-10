/** @file
    @brief defines database drivers, for work with facecope's database
*/
#ifndef FDATABASEDRIVER_H
#define FDATABASEDRIVER_H
#include <QMap>
#include <QSqlDriver>
#include <QSqlDriverCreatorBase>
#include <QSqlError>
#include <QString>
#include <Settings.h>
class FDatabaseDriver {
  QString path;
  QSqlDatabase db;
  Settings *settings;

public:
  FDatabaseDriver(Settings &settings);
  ~FDatabaseDriver();

  QMap<QString, QVariant> get_user(int id);
  QString get(int id, const QString &key);
  bool insert(const QString &key, const QString &value);
  int getNextId();
  bool set(int id, const QString &key, const QString &value);
  void closeDataBase();
  bool createTable();
  bool connectTo(const QString &path);

private:
  bool openDataBase(const QString &path);
  bool restoreDataBase();
};

#endif // FDATABASEDRIVER_H
