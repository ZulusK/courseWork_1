#include "FMainFacecopeModel.h"
#include <FFace.h>
#include <FFaceDetector.h>
#include <FFaceRecognizer.h>
#include <FacecopeTypes.h>
#include <QDebug>
#include <QFileIconProvider>
#include <QIcon>
#include <QImageReader>
#include <QPixmap>
#include <QString>
FMainFacecopeModel::FMainFacecopeModel(Facecope &facecope, QObject *parent)
    : QAbstractListModel(parent) {
  this->items = items;
  this->facecope = &facecope;
  this->items[QString("~/Projects/progbase3/res/people3.jpg")] =
      new FImage("/home/zulus/Projects/progbase3/res/people3.jpg");
  this->detected_count = 0;
  this->recognized_count = 0;
  this->detected_humans = 0;
  this->recognized_humans = 0;
}
FMainFacecopeModel::~FMainFacecopeModel() {
  foreach (auto image, items) { delete image; }
}

int FMainFacecopeModel::rowCount(const QModelIndex &parent) const {
  return items.size();
}

QVariant FMainFacecopeModel::data(const QModelIndex &index, int role) const {
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
      return ((QString)(items.begin() + index.row()).key().split("/").last())
          .mid(0, 7);
    }
  }
  return QVariant();
}

bool FMainFacecopeModel::load(const QString &path) {
  if (isValid_path(path)) {
    //
    beginInsertRows(QModelIndex(), 0, 0);
    //
    loader_mutex.lock();
    items.insert(items.begin(), path, new FImage(path));
    loader_mutex.unlock();
    //
    endInsertRows();
    //
    return true;
  }
  return false;
}

void FMainFacecopeModel::slot_set_image_size(const QSize &newSize) {
  image_scale_size = newSize;
}

const QMap<QString, FImage *> &FMainFacecopeModel::get_items() { return items; }

bool FMainFacecopeModel::remove(const QString &key) {
  if (items.contains(key)) {
    // calculate pos;
    int pos = items.keys().indexOf(key);
    //
    if (items[key]->isDetected()) {
      detected_count--;
      detected_humans -= items[key]->get_faces().size();
    }
    //
    beginRemoveRows(QModelIndex(), pos, pos);
    //
    loader_mutex.lock();
    items.remove(key);
    loader_mutex.unlock();
    //
    endRemoveRows();
    //
    return true;
  }
  return false;
}

bool FMainFacecopeModel::remove(int index) {
  if (index < 0 || index >= items.size()) {
    return false;
  } else {
    //
    beginRemoveRows(QModelIndex(), index, index);
    //
    loader_mutex.lock();
    items.remove((items.begin() + index).key());
    loader_mutex.unlock();
    //
    endRemoveRows();
    //
    return true;
  }
}

bool FMainFacecopeModel::isValid_path(const QString &key) {
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

FImage *FMainFacecopeModel::get_item(const QString &path) {
  if (items.contains(path)) {
    return items[path];
  } else {
    return NULL;
  }
}

FImage *FMainFacecopeModel::get_item(int index) {
  if (index < 0 || index >= items.size()) {
    return NULL;
  } else {
    return (items.begin() + index).value();
  }
}


QStringList FMainFacecopeModel::get_paths(){
    QStringList list;
    for(auto it=items.begin();it!=items.end();it++){
        list<<it.key();
    }
    return list;
}

void FMainFacecopeModel::slot_recognize(int row) {

  if (row >= 0 && row < items.size()) {
    auto image = get_item(row);
    if (!image->isRecognized() ||
        image->getThreahold_of_recognition() <
            facecope->settings->getThreahold()) {
      slot_detect(row);
      //
      recognized_count += !image->isRecognized();
      recognized_humans -= image->get_faces().size();
      //
      this->facecope->recognizer_gender->set_threahold(
          this->facecope->settings->getThreahold());
      foreach (auto face, image->get_faces()) {
        auto face_image = image->get_face_cv_image(face);
        int gender = facecope->recognizer_gender->recognize(face_image);
        int ID = facecope->recognizer_face->recognize(face_image);

        Human info;
        info.face = face;
        info.gender = gender;
        info.ID = ID;
        face->set_info(info);
      }
      image->set_recognized(true, facecope->settings->getThreahold());
      recognized_humans += image->get_faces().size();
    }
  }
}

void FMainFacecopeModel::slot_detect(int row) {
  if (row >= 0 && row < items.size()) {
    auto image = get_item(row);
    if (!image->isDetected() ||
        image->getDetection_steps() <
            facecope->settings->getSteps_of_detection()) {
      //
      detected_count += !image->isDetected();
      detected_humans -= image->get_faces().size();
      image->clear();
      //
      facecope->detector->detect_faces(
          *image, false,
          (facecope->settings->getCascade_type() == USE_LBP) ? LBP : HAAR,
          facecope->settings->getSteps_of_detection(), 360);
      image->set_detected(true, facecope->settings->getSteps_of_detection());
      image->set_recognized(false, -1);
      //
      detected_humans += image->get_faces().size();
    }
  }
}

bool FMainFacecopeModel::removeRow(int row, const QModelIndex &parent) {
  if (row >= 0 && row < items.size()) {
    return remove(row);
  } else {
    return false;
  }
}

void FMainFacecopeModel::slot_clear() {
  this->loader_mutex.lock();
  //
  beginRemoveRows(QModelIndex(), 0, items.size());
  //
  foreach (auto image, items) { delete image; }
  items.clear();
  //
  endRemoveRows();
  //
  this->detected_count = 0;
  this->detected_humans = 0;
  this->recognized_count = 0;
  this->recognized_humans = 0;
  this->loader_mutex.unlock();
}

int FMainFacecopeModel::get_detected_image_count() { return detected_count; }

int FMainFacecopeModel::get_recognized_image_count() {
  return recognized_count;
}

int FMainFacecopeModel::get_detected_faces_count() { return detected_humans; }

int FMainFacecopeModel::get_recognized_faces_count() {
  return recognized_humans;
}

int FMainFacecopeModel::get_loaded_images_count() { return items.size(); }
