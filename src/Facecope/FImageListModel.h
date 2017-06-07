#ifndef FIMAGELISTMODEL_H
#define FIMAGELISTMODEL_H

#include <QMap>
#include <QStandardItemModel>
#include <QString>
class FImageListModel : public QStandardItemModel {
  Q_OBJECT

public:
  explicit FImageListModel(QMap<QString, QImage> *images, QObject *parent = 0);

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QStandardItem *item(int row, int column = 0) const;
public slots:
  void update();

private:
  QMap<QString, QImage> *items;
};

#endif // FIMAGELISTMODEL_H
