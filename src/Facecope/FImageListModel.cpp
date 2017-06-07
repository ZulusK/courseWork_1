#include "FImageListModel.h"
#include <QDebug>
#include <QPixmap>
FImageListModel::FImageListModel(QMap<QString, QImage> *items, QObject *parent)
    : QAbstractListModel(parent) {
  this->items = items;
  for (int i = 0; i < 10; i++) {
    QString path =
        "~/Projects/progbase3/res/danil/Image" + QString::number(i) + ".jpg";
    QImage image(path);
    if (!image.isNull()) {
      items->insert(path,image);
    }
  }
}

QVariant FImageListModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {}

int FImageListModel::rowCount(const QModelIndex &parent) const {
  return items->size();
}

QVariant FImageListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (index.row() < 0 || index.row() >= items->size()) {
    return QVariant();
  }

//  if (role == Qt::DecorationRole) {
    return QVariant(QPixmap::fromImage((items->begin() + index.row()).value()));
//  } else {
//    return QVariant((items->begin() + index.row()).key());
//  }
}

bool FImageListModel::load(const QString filePath) {
  if ((!filePath.endsWith(".jpg") || !filePath.endsWith(".png")) &&
      items->contains(filePath)) {
    return false;
  } else {
    beginInsertRows(QModelIndex(), 0, 0);
    QImage newImage = QImage(filePath);
    endInsertRows();
    if (newImage.isNull()) {
      return false;
    }
    items->insert(filePath, newImage);
    qDebug() << "loaded" << endl;

    return true;
  }
}
