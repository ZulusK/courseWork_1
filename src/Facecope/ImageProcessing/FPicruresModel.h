#ifndef FPICRURESMODEL_H
#define FPICRURESMODEL_H
#include <FImage.h>
#include <FPicture.h>
#include <QStandardItemModel>
#include <QMap>
class FPicruresModel : public QStandardItemModel {
public:
  FPicruresModel(QObject *parent = 0);
  FPicruresModel(QMap<QString, FImage *> &items, QObject *parent = 0);
  ~FPicruresModel();
  int rowCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool add(const QString &filePath);
  QMap<QString, FImage *> &items();


private:
  QMap<QString, FImage *> images;
};

#endif // FPICRURESMODEL_H
