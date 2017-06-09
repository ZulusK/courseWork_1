#include "FImageDrawAreaWidget.h"
#include "ui_FImageDrawAreaWidget.h"
#include <FFace.h>
#include <QColor>
#include <QDebug>
#include <QPainter>

#define min(A, B) (((A) > (B)) ? (B) : (A))
FImageDrawAreaWidget::FImageDrawAreaWidget(Facecope &facecope, FImage &image,
                                           QWidget *parent)
    : QWidget(parent), ui(new Ui::FImageDrawAreaWidget) {
  this->f_image = &image;
  this->facecope = &facecope;
  ui->setupUi(this);
  this->recognized_female = QPen(QColor(244, 66, 185));
  this->recognized_male = QPen(QColor(0, 20, 250));
  this->unrecognized = QPen(QColor(255, 0, 20));
}

QSize FImageDrawAreaWidget::sizeHint() const { return f_image->q_size(); }

QSize FImageDrawAreaWidget::minimumSizeHint() const { return QSize(0, 0); }

FImageDrawAreaWidget::~FImageDrawAreaWidget() { delete ui; }
void FImageDrawAreaWidget::paintEvent(QPaintEvent *event) {

  QPainter painter(this);
  auto pix = QPixmap::fromImage(f_image->to_q_image().scaled(
      this->rect().size(), Qt::AspectRatioMode::KeepAspectRatio));
  QSize pix_size = pix.size();
  QPoint point((this->rect().width() - pix_size.width()) / 2,
               (this->rect().height() - pix_size.height()) / 2);
  painter.drawPixmap(point, pix);

  QSize original_size = f_image->q_size();

  float scale_factor = min((float)pix_size.width() / original_size.width(),
                           (float)pix_size.height() / original_size.height());
  foreach (auto face, f_image->get_faces()) {
    QRect face_frame = f_image->get_face_q_frame(face);
    QRect scaled_frame;
    scaled_frame.setX(face_frame.x() * scale_factor + point.x());
    scaled_frame.setY(face_frame.y() * scale_factor + point.y());
    scaled_frame.setWidth(face_frame.width() * scale_factor);
    scaled_frame.setHeight(face_frame.height() * scale_factor);
    painter.setPen(recognized_male);
    painter.drawRect(scaled_frame);
  }
}
