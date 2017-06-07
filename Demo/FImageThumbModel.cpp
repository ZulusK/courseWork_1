#include "FImageThumbModel.h"
#include <QDebug>
#include <QIcon>
#include <QPixmap>
FImageThumbModel::FImageThumbModel(QMap<QString, QImage> *items,
                                   QObject *parent)
    : QAbstractListModel(parent) {
  this->items = items;
}

int FImageThumbModel::rowCount(const QModelIndex &parent) const {
  return items->size();
}

QVariant FImageThumbModel::data(const QModelIndex &index, int role) const {
  qDebug() << "call data" << endl;
  if (!index.isValid())
    return QVariant();

  if (index.row() < 0 || index.row() >= this->items->size()) {
    return QVariant();
  } else {
    if (role == Qt::DecorationRole) {
      qDebug() << "return image" << endl;
      if ((items->begin() + index.row()).value().isNull()) {
        qDebug() << "!!!!!!!!!!!!!!!!!!!!image" << endl;
      }
      return QIcon(QPixmap::fromImage((items->begin() + index.row()).value()));

    } else if (role == Qt::DisplayRole) {
      qDebug() << "return text" << endl;
      return (items->begin() + index.row()).key();
    }
  }
  return QVariant();
}
