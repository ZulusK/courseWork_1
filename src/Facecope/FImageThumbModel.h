#ifndef FIMAGETHUMBMODEL_H
#define FIMAGETHUMBMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <QMap>
#include <QMutex>
#include <QSize>
#include <QString>

class FImageThumbModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit FImageThumbModel(QObject *parent = 0);
  ~FImageThumbModel();
  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  // methods for work with data
  const QMap<QString, QImage *> &get_items();
  bool load(const QString &path);
  bool remove(const QString &key);
  bool remove(int index);
  bool isValid_path(const QString &key);
  QImage *get_item(const QString &path);
  QImage *get_item(int index);

public slots:
  void set_image_size(const QSize &newSize);

private:
  QMutex loader_mutex;
  QMap<QString, QImage *> items;
  QSize image_scale_size;
};

#endif // FIMAGETHUMBMODEL_H
