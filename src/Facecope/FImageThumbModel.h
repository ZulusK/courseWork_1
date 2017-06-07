#ifndef FIMAGETHUMBMODEL_H
#define FIMAGETHUMBMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <QMap>
#include <QSize>
#include <QString>
class FImageThumbModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit FImageThumbModel(QMap<QString, QImage> *items, QObject *parent = 0);

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool load(const QString &path);
public slots:
  void set_image_size(const QSize & newSize);

private:
  QMap<QString, QImage> *items;
  QSize image_scale_size;
};

#endif // FIMAGETHUMBMODEL_H
