#include "FFaceModel.h"
#include <FacecopeUtils.h>
#include <QIcon>
#include <QPixmap>
FFaceModel::FFaceModel(FImage &f_image, Settings &settings, QObject *parent)
    : QAbstractTableModel(parent) {
  this->f_image = &f_image;
  this->settings = &settings;
  foreach (auto face, f_image.get_faces()) {
    faces.append(Mat2QImage(f_image.get_face_cv_image(face)));
  }
  this->icons_size = QSize(100, 100);
}

QVariant FFaceModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
  switch (section) {
  case 0:
    return QString("№");
    break;
  case 1:
    return QString("Face");
    break;
  case 2:
    return QString("Name");
    break;
  case 3:
    return QString("Gender");
    break;
  case 4:
    return QString("Assigned photos");
    break;
  default:
    return QVariant();
    break;
  }
}
int FFaceModel::rowCount(const QModelIndex &parent) const {
  return faces.size();
}

int FFaceModel::columnCount(const QModelIndex &parent) const { return 5; }

QVariant FFaceModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.column() >= columnCount() || index.row() < 0 ||
      index.row() >= rowCount())
    return QVariant();
  if (index.column() == 0 && role == Qt::SizeHintRole) {
    return icons_size;
  }
  switch (index.column()) {
  case 0:
    if (role == Qt::DisplayRole) {
      return QString::number(f_image->get_face(index.row())->get_ID());
    }
    break;
  case 1:
    if (role == Qt::SizeHintRole) {
      return icons_size;
    } else if (role == Qt::DecorationRole) {
      return QPixmap::fromImage(faces[index.row()].scaled(
          icons_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    break;
  case 2:
    if (role == Qt::DisplayRole) {
      auto face = this->f_image->get_face(index.row);
      if (face) {
        auto name = face->get_info().name;
        if (name.length() == 0) {
          return QString("Not recognized");
        } else {
          return name;
        }
      }
    }
    break;
  case 3:
    if (role == Qt::DisplayRole) {
      auto face = this->f_image->get_face(index.row);
      if (face) {
        return (gender == MALE) ? "Male"
                                : (gender == FEMALE) ? "Female" : "Male/Female";
      }
    }

    break;
  case 4:
    if (role == Qt::DisplayRole) {
      return "12334";
    }
    break;
  }
  return QVariant();
}

void FFaceModel::set_image_size(const QSize &newSize) {
  this->icons_size = newSize;
}
