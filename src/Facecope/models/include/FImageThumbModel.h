#ifndef FIMAGETHUMBMODEL_H
#define FIMAGETHUMBMODEL_H

#include <FImage.h>
#include <FacecopeTypes.h>
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
  explicit FImageThumbModel(FacecopeProcessors &processors, Settings &settings,
                            QObject *parent = 0);
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
  FacecopeProcessors *get_processors() const;
  // methods for statistics
  int get_detected_image_count();
  int get_recognized_image_count();
  int get_detected_faces_count();
  int get_recognized_faces_count();
  int get_loaded_images_count();

public slots:
  void slot_set_image_size(const QSize &newSize);
  void slot_clear();
  void slot_recognize(int row);
  void slot_detect(int row);

private:
  QMutex loader_mutex;
  QMap<QString, FImage *> items;
  QSize image_scale_size;
  Settings *settings;
  FacecopeProcessors *processors;
  int detected_count;

  int recognized_count;

  int detected_humans;

  int recognized_humans;
};

#endif // FIMAGETHUMBMODEL_H
