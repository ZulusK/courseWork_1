#include "FPicruresModel.h"

FPicruresModel::FPicruresModel(QObject *parent ) {}

FPicruresModel::FPicruresModel(QMap<QString, FImage *> &items,
                               QObject *parent ) {
  this->images = items;
}

FPicruresModel::~FPicruresModel() {}

int FPicruresModel::rowCount(const QModelIndex &parent) const {
  return images.size();
}
QVariant FPicruresModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.row() >= images.size() || index.row() < 0)
    return QVariant();

  if (role == Qt::DisplayRole) {
    FImage f_image = *(images.begin()+index.row()).value();
    return QVariant(QImage((unsigned char *)f_image.get_image().data,
                           f_image.get_size().width, f_image.get_size().height,
                           f_image.get_image().step, QImage::Format_RGB888)
                        .rgbSwapped());
  }
  return QVariant();
}

bool FPicruresModel::add(const QString &filePath) {
  if (images.contains(filePath)) {
    return false;
  } else {
    auto f_image = new FImage(filePath.toStdString());
    if (f_image->empty()) {
      delete f_image;
      return false;
    }
    this->images[filePath] = f_image;
    return true;
  }
}

QMap<QString, FImage *> &FPicruresModel::items() { return images; }
