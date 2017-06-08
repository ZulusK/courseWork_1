#include "FImageDrawAreaWidget.h"
#include "ui_FImageDrawAreaWidget.h"
#include <QPainter>
FImageDrawAreaWidget::FImageDrawAreaWidget(FImage &image, Settings &settings,
                                           QWidget *parent)
    : QWidget(parent), ui(new Ui::FImageDrawAreaWidget) {
  this->f_image = &image;
  this->settings = &settings;
  ui->setupUi(this);
}

QSize FImageDrawAreaWidget::sizeHint() const { return f_image->q_size(); }

QSize FImageDrawAreaWidget::minimumSizeHint() const { return QSize(0, 0); }

FImageDrawAreaWidget::~FImageDrawAreaWidget() { delete ui; }
void FImageDrawAreaWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawPixmap(
      this->rect(),
      QPixmap::fromImage(f_image->to_q_image().scaled(
          this->rect().size(), Qt::AspectRatioMode::KeepAspectRatio)));
}
