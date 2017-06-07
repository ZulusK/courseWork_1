#include "FImageThumbModel.h"
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QString>
FImageThumbModel::FImageThumbModel(QMap<QString, QImage> *items,
                                   QObject *parent)
    : QAbstractListModel(parent) {
  this->items = items;
  (*this->items)[QString("~/Projects/progbase3/res/people.jpg")] =
      QImage("/home/zulus/Projects/progbase3/res/people.jpg");
}

int FImageThumbModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "row count " << items->size();
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
      return QIcon(QPixmap::fromImage(
          (items->begin() + index.row())
              .value()
              .scaled(image_scale_size, Qt::KeepAspectRatio)));

    } else if (role == Qt::DisplayRole) {
      qDebug() << "return text" << endl;
      return ((QString)(items->begin() + index.row()).key().split("/").last())
          .mid(0, 7);
    }
  }
  return QVariant();
}

bool FImageThumbModel::load(const QString &path) {
  qDebug() << "try to insert" + path;
  if (!items->contains(path)) {
    QImage image(path);
    if (!image.isNull()) {
      beginInsertRows(QModelIndex(), 0, 0);
      items->insert(items->begin(), path, image);
      qDebug() << "inserted" + path;
      endInsertRows();
      emit dataChanged(index(0, 0), index(items->size() - 1, 0));
      return true;
    }
  }
  return false;
}

void FImageThumbModel::set_image_size(const QSize &newSize) {
  image_scale_size = newSize;
}
