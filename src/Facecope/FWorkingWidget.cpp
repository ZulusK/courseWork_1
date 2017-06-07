#include "FWorkingWidget.h"
#include "ui_FWorkingWidget.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QFileIconProvider>
#include <QIcon>
#include <QMimeData>

FWorkingWidget::FWorkingWidget(QMap<QString, QImage> *images, QWidget *parent)
    : QWidget(parent), ui(new Ui::FWorkingWidget) {
  QThreadPool::globalInstance()->setMaxThreadCount(1);
  ui->setupUi(this);
  setAcceptDrops(true);
  this->list_model = new QStandardItemModel(this);
  ui->item_view->setModel(list_model);
  connect(this, SIGNAL(UpdateItem(QString, QImage)),
          SLOT(setThumbs(QString, QImage)));
  //  QSize listIconSize = ui->item_view->iconSize();
  //  ui->item_view->setIconSize(
  //      QSize(listIconSize.width() / 3, listIconSize.width() * 4 / 9));
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
  thread.waitForFinished();
  QFileIconProvider fileIcon;
  QIcon placeHolder = fileIcon.icon(QFileIconProvider::File);

  int i = 0;
  foreach (const QUrl &url, e->mimeData()->urls()) {
    QString fileName = url.toLocalFile();
    qDebug() << "Dropped file:" << fileName;
    list_model->setItem(
        list_model->rowCount() + i,
        new QStandardItem(placeHolder, fileName.split("/").last()));
  }
  thread = QtConcurrent::run(this, &FWorkingWidget::addImages,
                             e->mimeData()->urls(), ui->item_view->iconSize());
}

void FWorkingWidget::addImages(QList<QUrl> urls, QSize size) {
  foreach (const QUrl &url, urls) {
    QImage originalImage(url.toLocalFile());
    if (!originalImage.isNull()) {
      QImage scaledImage =
          originalImage.scaled(QSize(300,200), Qt::AspectRatioMode::KeepAspectRatio);
      emit UpdateItem(url.toLocalFile(), scaledImage);
    }
  }
}

void FWorkingWidget::setThumbs(QString index, QImage img) {
  QIcon icon = QIcon(QPixmap::fromImage(img));
  QStandardItem *item = list_model->findItems(index.split("/").last()).at(0);
  qDebug()<<index.split("/").last();
  list_model->setItem(item->row(), new QStandardItem(icon, item->text()));
}
