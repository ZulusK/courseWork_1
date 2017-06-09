#include "FImageProxyModel.h"
#include <QDebug>
FImageProxyModel::FImageProxyModel(FMainFacecopeModel &src_model,
                                   QObject *parent)
    : QSortFilterProxyModel(parent) {
  this->src_model = &src_model;
  clear();
}

void FImageProxyModel::clear() {
  this->show_only_human = false;
  this->show_recognized = false;
  this->show_unrecognized = false;
  this->show_without_human = false;
  this->min_human_number = 0;
}

bool FImageProxyModel::isValid(FImage *image) const{
  if (image->get_faces().size() < min_human_number) {
    return false;
  }
  if (show_only_human && !image->isDetected()) {
    return false;
  }
  if (show_recognized && !image->isRecognized()) {
    return false;
  }
  if (show_unrecognized && image->isRecognized()) {
    return false;
  }
  return true;
}

FImageProxyModel::~FImageProxyModel() {}

bool FImageProxyModel::filterAcceptsRow(int source_row,
                                        const QModelIndex &source_parent) const{
  if (source_row >= this->sourceModel()->rowCount() || source_row < 0) {
    return false;
  } else {
    return isValid(src_model->get_item(source_row));
  }
}

int FImageProxyModel::getDisplaingPhotos() { return this->rowCount(); }

void FImageProxyModel::setShow_recognized(bool value) {
  show_recognized = value;
  qDebug() << "1";
}

void FImageProxyModel::setShow_unrecognized(bool value) {
  show_unrecognized = value;
  qDebug() << "2";
}

void FImageProxyModel::apply() { invalidateFilter(); }

void FImageProxyModel::setShow_without_human(bool value) {
  show_without_human = value;
}

void FImageProxyModel::setShow_only_human(bool value) {
  show_only_human = value;
  qDebug() << "3";
}

void FImageProxyModel::setMin_human_number(int value) {
  min_human_number = value;
  qDebug() << "4";
}
