#include "FImageThumbModel.h"
#include <FFaceDetector.h>
#include <QDebug>
#include <QFileIconProvider>
#include <QIcon>
#include <QImageReader>
#include <QPixmap>
#include <QString>

FImageThumbModel::FImageThumbModel(FacecopeProcessors &processors,
                                   Settings &settings, QObject *parent)
    : QAbstractListModel(parent) {
  this->items = items;
  this->settings = &settings;
  this->processors = &processors;
  this->items[QString("~/Projects/progbase3/res/people3.jpg")] =
      new FImage("/home/zulus/Projects/progbase3/res/people3.jpg");
}
FImageThumbModel::~FImageThumbModel() {
  foreach (auto image, items) { delete image; }
}

int FImageThumbModel::rowCount(const QModelIndex &parent) const {
  //  qDebug() << "row count " << items.size();
  return items.size();
}

QVariant FImageThumbModel::data(const QModelIndex &index, int role) const {
  //  qDebug() << "call data" << endl;
  if (!index.isValid())
    return QVariant();

  if (index.row() < 0 || index.row() >= this->items.size()) {
    return QVariant();
  } else {
    if (role == GET_FULL_ITEM_PATH) {
      return (QString)(items.begin() + index.row()).key();
    } else if (role == Qt::DecorationRole) {
      if ((items.begin() + index.row()).value()->empty()) {
        return QFileIconProvider::File;
      } else {
        return QIcon(QPixmap::fromImage(
            (items.begin() + index.row())
                .value()
                ->to_q_image()
                .scaled(image_scale_size,
                        Qt::AspectRatioMode::KeepAspectRatio)));
      }
    } else if (role == Qt::DisplayRole) {
      //      qDebug() << "return text" << endl;
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
    items.insert(items.begin(), path, new FImage(path));
    loader_mutex.unlock();
    qDebug() << "inserted" + path;
    endInsertRows();
    return true;
  }
  return false;
}

void FImageThumbModel::set_image_size(const QSize &newSize) {
  image_scale_size = newSize;
}

const QMap<QString, FImage *> &FImageThumbModel::get_items() { return items; }

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

FImage *FImageThumbModel::get_item(const QString &path) {
  if (items.contains(path)) {
    return items[path];
  } else {
    return NULL;
  }
}

FImage *FImageThumbModel::get_item(int index) {
  if (index < 0 || index >= items.size()) {
    return NULL;
  } else {
    return (items.begin() + index).value();
  }
}

FacecopeProcessors *FImageThumbModel::get_processors() const {
  return this->processors;
}

void FImageThumbModel::recognize(int row) {
  qDebug() << "call recognize";
  if (row >= 0 && row < items.size()) {
  }
}

void FImageThumbModel::detect(int row) {
  qDebug() << "call detect";
  if (row >= 0 && row < items.size()) {
    this->processors->detector->detect_faces(*get_item(row),false,HAAR,10,360);
    qDebug() << "end detecting";
  }
}

bool FImageThumbModel::removeRow(int row, const QModelIndex &parent) {
  //  qDebug() << "call remove " << row;
  if (row >= 0 && row < items.size()) {
    return remove(row);
  } else {
    return false;
  }
}

void FImageThumbModel::clear() {
  this->loader_mutex.lock();
  beginRemoveRows(QModelIndex(), 0, items.size());
  foreach (auto image, items) { delete image; }
  items.clear();
  endRemoveRows();
  this->loader_mutex.unlock();
}
