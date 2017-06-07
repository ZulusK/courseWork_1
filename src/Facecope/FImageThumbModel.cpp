#include "FImageThumbModel.h"
#include <QDebug>
#include <QFileIconProvider>
#include <QIcon>
#include <QImageReader>
#include <QPixmap>
#include <QString>
FImageThumbModel::FImageThumbModel(QObject *parent)
    : QAbstractListModel(parent) {
  this->items = items;
  this->items[QString("~/Projects/progbase3/res/people.jpg")] =
      new QImage("/home/zulus/Projects/progbase3/res/people.jpg");
}
FImageThumbModel::~FImageThumbModel() {
  foreach (QImage *image, items) { delete image; }
}

int FImageThumbModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "row count " << items.size();
  return items.size();
}

QVariant FImageThumbModel::data(const QModelIndex &index, int role) const {
  qDebug() << "call data" << endl;
  if (!index.isValid())
    return QVariant();

  if (index.row() < 0 || index.row() >= this->items.size()) {
    return QVariant();
  } else {
    if (role == Qt::DecorationRole) {
      qDebug() << "return image" << endl;
      if ((items.begin() + index.row()).value()->isNull()) {
        return QFileIconProvider::File;
      } else {
        return QIcon(QPixmap::fromImage(
            (items.begin() + index.row())
                .value()
                ->scaled(image_scale_size,
                         Qt::AspectRatioMode::KeepAspectRatio)));
      }
    } else if (role == Qt::DisplayRole) {
      qDebug() << "return text" << endl;
      return ((QString)(items.begin() + index.row()).key().split("/").last())
          .mid(0, 7);
    }
  }
  return QVariant();
}

bool FImageThumbModel::load(const QString &path) {
  qDebug() << "try to insert" + path;
  if (isValid_path(path)) {
    beginInsertRows(QModelIndex(), 0, 0);
    loader_mutex.lock();
    items.insert(items.begin(), path, new QImage(path));
    loader_mutex.unlock();
    qDebug() << "inserted" + path;
    endInsertRows();
    emit dataChanged(index(0, 0), index(items.size() - 1, 0));
    return true;
  }
  return false;
}

void FImageThumbModel::set_image_size(const QSize &newSize) {
  image_scale_size = newSize;
}

const QMap<QString, QImage *> &FImageThumbModel::get_items() { return items; }

bool FImageThumbModel::remove(const QString &key) {
  if (items.contains(key)) {
    // calculate pos;
    int pos = items.keys().indexOf(key);
    beginRemoveRows(QModelIndex(), pos, pos);
    loader_mutex.lock();
    items.remove(key);
    loader_mutex.unlock();
    endRemoveRows();
    return true;
  }
  return false;
}

bool FImageThumbModel::remove(int index) {
  if (index < 0 || index >= items.size()) {
    return false;
  } else {

    beginRemoveRows(QModelIndex(), index, index);
    loader_mutex.lock();
    items.remove((items.begin() + index).key());
    loader_mutex.unlock();
    endRemoveRows();

    return true;
  }
}

bool FImageThumbModel::isValid_path(const QString &key) {
  if (items.contains(key)) {
    return false;
  }
  QImageReader reader(key);
  if (reader.format().size() == 0) {
    qDebug() << "reader can't read file";
    return false;
  }
  return true;
}

QImage *FImageThumbModel::get_item(const QString &path) {
  if (items.contains(path)) {
    return items[path];
  } else {
    return NULL;
  }
}

QImage *FImageThumbModel::get_item(int index) {
  if (index < 0 || index >= items.size()) {
    return NULL;
  } else {
    return (items.begin() + index).value();
  }
}
