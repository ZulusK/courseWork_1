#ifndef FIMAGETHUMBMODEL_H
#define FIMAGETHUMBMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <QMap>
#include <QString>

class FImageThumbModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit FImageThumbModel(QMap<QString, QImage> *items, QObject *parent = 0);

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

private:
  QMap<QString, QImage> *items;
};

#endif // FIMAGETHUMBMODEL_H
