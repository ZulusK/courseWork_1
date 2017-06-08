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
  auto pix = QPixmap::fromImage(f_image->to_q_image().scaled(
      this->rect().size(), Qt::AspectRatioMode::KeepAspectRatio));
  QPoint point((this->rect().width()-pix.width())/2,(this->rect().height()-pix.height())/2);
  painter.drawPixmap(point, pix);
}
