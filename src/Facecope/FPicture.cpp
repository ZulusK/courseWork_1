#include "FPicture.h"
#include "ui_FPicture.h"
#include <QPainter>

FImage *load_image(const QString &path) {
  auto f_image = new FImage(path.toStdString());
  if (f_image->empty()) {
    delete f_image;
    return NULL;
  } else {
    return f_image;
  }
}

FPicture::FPicture(const QString &imagePath, QWidget *parent)
    : QWidget(parent) {
  this->f_image = load_image(imagePath);
  if (f_image) {
    toQImage(*f_image, q_image);
  }
  ui->setupUi(this);
}

FPicture::FPicture(FImage *image, QWidget *parent) {
  set_image(image);
  ui->setupUi(this);
}

FPicture::~FPicture() {
  delete ui;
}

void FPicture::set_image(FImage *image) {
  this->f_image = image;
  if (f_image) {
    toQImage(*f_image, q_image);
  }
}

void FPicture::draw_faceArea(QPainter &painter, long id) {}

void FPicture::draw_image(QPainter &painter) {}

QSize FPicture::minimumSizeHint() const { return QSize(50, 50); }

QSize FPicture::sizeHint() const { return QSize(200, 200); }

void FPicture::toQImage(FImage &f_image, QImage &q_image) {
  q_image = QImage((unsigned char *)f_image.get_image().data,
                   f_image.get_size().width, f_image.get_size().height,
                   f_image.get_image().step, QImage::Format_RGB888)
                .rgbSwapped();
}

void FPicture::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawImage(QPoint(),
                    q_image.scaled(this->rect().size(), Qt::KeepAspectRatio));
}
