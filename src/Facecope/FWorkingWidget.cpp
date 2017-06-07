#include "FWorkingWidget.h"
#include "ui_FWorkingWidget.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QProgressDialog>
FWorkingWidget::FWorkingWidget(FImageThumbModel *model, QWidget *parent)
    : QWidget(parent), ui(new Ui::FWorkingWidget) {
  this->model = model;

  ui->setupUi(this);
  setAcceptDrops(true);
  connect(this,SIGNAL(images_added(QList<QUrl>)),this,SLOT(addImages(QList<QUrl>)));
  on_horizontalSlider_sliderMoved(ui->horizontalSlider->value());
  ui->list_view->setModel(model);
}

FWorkingWidget::~FWorkingWidget() { delete ui; }

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
  emit images_added(e->mimeData()->urls());
}

void FWorkingWidget::addImages(const QList<QUrl> &urls) {
  QProgressDialog dialog(this);
  dialog.setCancelButtonText(tr("&Cancel"));
  dialog.setWindowTitle(tr("Wait for loading"));
  dialog.setRange(0, urls.size());
  for (int i = 0; i < urls.size(); i++) {
    dialog.setLabelText(QString("load ") +
                        urls.at(i).toLocalFile().split("/").last());
    dialog.setValue(i);
    if (dialog.wasCanceled()) {
      break;
    }
    model->load(urls.at(i).toLocalFile());
    QCoreApplication::processEvents();
  }
  dialog.hide();
}

void FWorkingWidget::on_horizontalSlider_sliderMoved(int position) {
  float width = ui->list_view->rect().width() * position / 100.0;
  float height = ui->list_view->rect().height() * position / 100.0;
  this->model->set_image_size(QSize(width, height));
  this->ui->list_view->setIconSize(QSize(width, height));
}
