#include "FPicture.h"
#include "ui_FPicture.h"
#include <QPainter>
FPicture::FPicture(const QString &imagePath, FMainWindow *parent)
    : QWidget(parent) {
  ui->setupUi(this);
  this->parent= parent;
  this->f_image = new FImage(imagePath.toStdString());
  this->image_data = f_image->get_image().data;
}

FPicture::~FPicture() {
  delete ui;
  delete f_image;
}

QSize FPicture::minimumSizeHint() const { return QSize(50, 50); }

QSize FPicture::sizeHint() const { return QSize(200, 200); }

void FPicture::paintEvent(QPaintEvent *event) {
  auto pix = QPixmap::fromImage(
      QImage((unsigned char *)image_data, f_image->get_size().width,
             f_image->get_size().height,f_image->get_image().step, QImage::Format_RGB888).rgbSwapped());
  QPainter painter(this);
  painter.drawPixmap(QRect(0,0,f_image->get_size().width,f_image->get_size().height),pix);
}
