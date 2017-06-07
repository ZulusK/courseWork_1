#include "FImageListModel.h"
#include <QDebug>
FImageListModel::FImageListModel(QMap<QString, QImage> *images, QObject *parent)
    : QStandardItemModel(parent) {
  this->items = images;
}

int FImageListModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return items->size();
  } else {
    return 0;
  }
}
int FImageListModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 1;
  } else {
    return 0;
  }
}

QVariant FImageListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.column() > 0 || index.row() < 0 || index.row() > items->size()) {
    return QVariant();
  }
  if (role == Qt::DecorationRole) {
    return QVariant(QPixmap::fromImage((items->begin() + index.row()).value()));
  } else {
    return QVariant((items->begin() + index.row()).key());
  }
  return QVariant();
}

void FImageListModel::update() { this->itemChanged(QStandardItem()); }
