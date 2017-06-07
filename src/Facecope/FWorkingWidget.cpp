#include "FWorkingWidget.h"
#include "ui_FWorkingWidget.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QIcon>
#include <QMimeData>

FWorkingWidget::FWorkingWidget(QMap<QString, QImage> *images, QWidget *parent)
    : QWidget(parent), ui(new Ui::FWorkingWidget) {
  ui->setupUi(this);
  setAcceptDrops(true);
  this->list_model = new FImageThumbModel(images, this);
  ui->list_view->setModel(list_model);
  on_horizontalSlider_sliderMoved(ui->horizontalSlider->value());
  //  connect(this, SIGNAL(UpdateItem(const QString &)), this, SLOT(add));
}

FWorkingWidget::~FWorkingWidget() {
  delete ui;
  delete list_model;
}

void FWorkingWidget::dragEnterEvent(QDragEnterEvent *e) {
  if (e->mimeData()->hasUrls()) {
    e->acceptProposedAction();
  }
}

void FWorkingWidget::dropEvent(QDropEvent *e) {
  foreach (const QUrl &url, e->mimeData()->urls()) {
    QString fileName = url.toLocalFile();
    qDebug() << "Dropped file:" << fileName;
  }
  addImages(e->mimeData()->urls());
}

void FWorkingWidget::addImages(const QList<QUrl> &urls) {
  qDebug() << "start loop ";
  foreach (const QUrl &url, urls) {
    qDebug() << "try to emit: ";
    list_model->load(url.toLocalFile());
  }
}

void FWorkingWidget::addImagesToModel(const QString &path) {
  qDebug() << "try to add  file:" << path;
  list_model->load(path);
}

void FWorkingWidget::on_horizontalSlider_sliderMoved(int position) {
  float width = ui->list_view->rect().width() * position / 100.0;
  float height = ui->list_view->rect().height() * position / 100.0;
  this->list_model->set_image_size(QSize(width, height));
  this->ui->list_view->setIconSize(QSize(width, height));
}
