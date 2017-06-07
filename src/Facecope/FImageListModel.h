#ifndef FIMAGELISTMODEL_H
#define FIMAGELISTMODEL_H

#include <QAbstractListModel>
#include <QMap>
class FImageListModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit FImageListModel(QMap<QString, QImage> *items, QObject *parent = 0);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QMap<QString, QImage> *get_items();

  bool load(const QString filePath);
private:
  QMap<QString, QImage> *items;
};

#endif // FIMAGELISTMODEL_H
