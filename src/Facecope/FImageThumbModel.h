#ifndef FIMAGETHUMBMODEL_H
#define FIMAGETHUMBMODEL_H

#include <FImage.h>
#include <QAbstractListModel>
#include <QImage>
#include <QMap>
#include <QMutex>
#include <QSize>
#include <QString>
#include <Settings.h>

enum { GET_FULL_ITEM_PATH = -1 };
class FImageThumbModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit FImageThumbModel(Settings &settings, QObject *parent = 0);
  ~FImageThumbModel();
  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool removeRow(int row, const QModelIndex &parent = QModelIndex());

  // methods for work with data
  const QMap<QString, FImage *> &get_items();
  bool load(const QString &path);
  bool remove(const QString &key);
  bool remove(int index);
  bool isValid_path(const QString &key);
  FImage *get_item(const QString &path);
  FImage *get_item(int index);

public slots:
  void set_image_size(const QSize &newSize);
  void clear();

private:
  QMutex loader_mutex;
  QMap<QString, FImage *> items;
  QSize image_scale_size;
  Settings *settings;
};

#endif // FIMAGETHUMBMODEL_H
