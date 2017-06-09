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
  FDatabaseDriver(Settings & settings );
  ~FDatabaseDriver();

  QMap<QString, QVariant> get_user(int id);

  void closeDataBase();
  bool createTable();
  bool connectTo(const QString &path);

private:
  bool openDataBase(const QString &path);
  bool restoreDataBase();
};

#endif // FDATABASEDRIVER_H
