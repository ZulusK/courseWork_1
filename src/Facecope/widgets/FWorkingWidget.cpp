#include "FWorkingWidget.h"
#include "ui_FWorkingWidget.h"
#include <FImageShowDialog.h>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QModelIndexList>
#include <QProgressDialog>
#include <QSet>
FWorkingWidget::FWorkingWidget(Settings &settings, FImageThumbModel *model,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::FWorkingWidget) {
  this->model = model;
  this->settings = &settings;
  ui->setupUi(this);
  setUp();
}

void FWorkingWidget::setUp() {
  setAcceptDrops(true);
  this->model_proxy = new FImageProxyModel();
  this->model_proxy->setSourceModel(model);
  ui->list_view->setModel(model_proxy);

  this->completer = new QCompleter(this);
  this->completer->setModel(ui->selecthuman_CB->model());
  this->completer->setCaseSensitivity(Qt::CaseSensitive);
  ui->selecthuman_CB->setCompleter(completer);

  connect(this, SIGNAL(signal_load_images(QList<QUrl>)), this,
          SLOT(slot_add_images(QList<QUrl>)));
  connect(this, SIGNAL(signal_load_images(QStringList)), this,
          SLOT(slot_add_images(QStringList)));
  connect(this, SIGNAL(signal_detect_face(int)), model, SLOT(slot_detect(int)));
  connect(this, SIGNAL(signal_images_changed()), this,
          SLOT(slot_update_labels()));
  on_sizeSlider_sliderMoved(300);
  emit signal_images_changed();
}

FWorkingWidget::~FWorkingWidget() {
  delete ui;
  delete model_proxy;
  delete completer;
}

void FWorkingWidget::slot_update_labels() {
  int deteted_photos = model->get_detected_image_count();
  int recognized_photos = model->get_recognized_image_count();

  int detected_humans = model->get_detected_faces_count();
  int recognized_humans = model->get_recognized_faces_count();

  int loaded_photos = model->get_loaded_images_count();
  int displaying_photos = model_proxy->getDisplaingPhotos();

  ui->loaded_E->setText(QString::number(loaded_photos));
  ui->showImage_E->setText(QString::number(displaying_photos));

  ui->detectedPhotos_E->setText(QString::number(deteted_photos));
  ui->recognizedPhotos_E->setText(QString::number(recognized_photos));

  ui->detected_E->setText(QString::number(detected_humans));
  ui->recognized_E->setText(QString::number(recognized_humans));
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
  emit signal_load_images(e->mimeData()->urls());
}

void FWorkingWidget::slot_add_images(const QList<QUrl> &urls) {
  QStringList paths;
  foreach (QUrl url, urls) {
    if (model->isValid_path(url.toLocalFile())) {
      paths.append(url.toLocalFile());
    }
  }
  slot_add_images(paths);
}

void FWorkingWidget::slot_add_images(const QStringList &urls) {
  QProgressDialog dialog(this);
  dialog.setCancelButtonText(tr("&Cancel"));
  dialog.setWindowTitle(tr("Wait for loading"));
  dialog.setRange(0, urls.size());
  for (int i = 0; i < urls.size(); i++) {
    dialog.setLabelText(tr("load ") + urls.at(i).split("/").last());
    dialog.setValue(i);
    if (dialog.wasCanceled()) {
      break;
    }
    model->load(urls.at(i));
    emit signal_images_changed();
    QCoreApplication::processEvents();
  }
  dialog.hide();
}

void FWorkingWidget::on_sizeSlider_sliderMoved(int position) {
  float width = ui->list_view->rect().width() * position / 100.0;
  float height = ui->list_view->rect().height() * position / 100.0;
  this->model->slot_set_image_size(QSize(width, height));
  this->ui->list_view->setIconSize(QSize(width, height));
}

void FWorkingWidget::on_list_view_doubleClicked(const QModelIndex &index) {
  this->model->slot_detect(model_proxy->mapToSource(index).row());
  emit signal_images_changed();
  FImageShowDialog dialog(*model->get_item(index.row()), *settings, this);
  dialog.exec();
}

void FWorkingWidget::slot_remove_selected() {
  auto indexList = ui->list_view->selectionModel()->selectedRows();
  foreach (auto proxy_index, indexList) {
    model->removeRow(model_proxy->mapToSource(proxy_index).row());
  }
  emit signal_images_changed();
}

void FWorkingWidget::on_selecthuman_CB_currentIndexChanged(int index) {
  emit signal_images_changed();
}

void FWorkingWidget::on_show_rec_RB_clicked() { emit signal_images_changed(); }

void FWorkingWidget::on_show_UR_RB_clicked() { emit signal_images_changed(); }

void FWorkingWidget::on_detect_B_clicked() {
  QProgressDialog dialog(this);
  dialog.setCancelButtonText(tr("&Cancel"));
  dialog.setWindowTitle(tr("Wait while detection is running"));
  dialog.setRange(0, model->get_loaded_images_count());

  for (int pos = 0; pos < model->get_loaded_images_count(); pos++) {
    dialog.setLabelText(tr("process ") + model->get_item(pos)->get_name());
    dialog.setValue(pos++);
    if (dialog.wasCanceled()) {
      break;
    }
    this->model->slot_detect(pos);
    QCoreApplication::processEvents();
    emit signal_images_changed();
  }
  dialog.hide();
}

void FWorkingWidget::on_recognize_B_clicked() { emit signal_images_changed(); }

void FWorkingWidget::on_save_B_clicked() {}

void FWorkingWidget::on_clear_B_clicked() {}

void FWorkingWidget::on_show_woman(bool enable) {
  emit signal_images_changed();
}

void FWorkingWidget::on_show_man(bool enable) { emit signal_images_changed(); }

void FWorkingWidget::on_showAll_RB_clicked()
{

}
