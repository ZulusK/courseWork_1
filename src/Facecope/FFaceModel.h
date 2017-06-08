#ifndef FFACEMODEL_H
#define FFACEMODEL_H

#include <FFace.h>
#include <FImage.h>
#include <QAbstractTableModel>
#include <Settings.h>
class FFaceModel : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit FFaceModel(FImage &f_image, Settings &settings, QObject *parent = 0);

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
public slots:
  void set_image_size(const QSize &newSize);

private:
  QList<QImage> faces;
  FImage *f_image;
  Settings *settings;
  QSize icons_size;
};

#endif // FFACEMODEL_H
