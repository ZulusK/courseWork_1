#include "FWorkingWidget.h"
#include "ui_FWorkingWidget.h"
#include <FImageShowDialog.h>
#include <QDebug>
#include <QDir>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QModelIndexList>
#include <QProgressDialog>
#include <QSet>
FWorkingWidget::FWorkingWidget(Facecope &facecope, FMainFacecopeModel *model,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::FWorkingWidget) {
  this->model = model;
  this->facecope = &facecope;
  ui->setupUi(this);

  setUp();
}

void FWorkingWidget::setUp() {
  setAcceptDrops(true);
  this->model_proxy = new FImageProxyModel(*model, this);
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
  //  this->model->slot_detect(model_proxy->mapToSource(index).row());
  this->model->slot_recognize(model_proxy->mapToSource(index).row());
  emit signal_images_changed();
  FImageShowDialog dialog(*facecope, *model->get_item(index.row()), this);
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

void FWorkingWidget::on_show_rec_RB_clicked() {
  model_proxy->setShow_recognized(true);
  model_proxy->setShow_unrecognized(false);
  model_proxy->apply();
  emit signal_images_changed();
}

void FWorkingWidget::on_show_UR_RB_clicked() {

  model_proxy->setShow_recognized(false);
  model_proxy->setShow_unrecognized(true);
  model_proxy->apply();
  emit signal_images_changed();
}

void FWorkingWidget::on_detect_B_clicked() {
  QProgressDialog dialog(this);
  dialog.setCancelButtonText(tr("&Cancel"));
  dialog.setWindowTitle(tr("Wait while detection is running"));
  dialog.setRange(0, model->get_loaded_images_count());

  for (int pos = 0; pos < model->get_loaded_images_count(); pos++) {
    dialog.setLabelText(tr("process ") + model->get_item(pos)->get_name());
    this->model->slot_detect(pos);
    dialog.setValue(pos++);
    if (dialog.wasCanceled()) {
      break;
    }
    QCoreApplication::processEvents();
    emit signal_images_changed();
  }
  dialog.hide();
}

void FWorkingWidget::on_recognize_B_clicked() {
  qDebug() << "recognize called";
  QProgressDialog dialog(this);
  dialog.setCancelButtonText(tr("&Cancel"));
  dialog.setWindowTitle(tr("Wait while program is computing"));
  dialog.setRange(0, model->get_loaded_images_count());

  for (int pos = 0; pos < model->get_loaded_images_count(); pos++) {
    dialog.setLabelText(tr("process ") + model->get_item(pos)->get_name());
    this->model->slot_recognize(pos);
    dialog.setValue(pos++);
    if (dialog.wasCanceled()) {
      break;
    }
    QCoreApplication::processEvents();
    emit signal_images_changed();
  }
  dialog.hide();
}

void FWorkingWidget::on_save_B_clicked() {
  if (!QDir(facecope->settings->getOutput_path()).exists()) {
    // create dir
    QDir().mkdir(facecope->settings->getOutput_path());
  }
  QString newpath = facecope->settings->getOutput_path();
  QString home = QDir::home().absolutePath();
  newpath.replace("~", home);
  newpath += "/Facecope Output";
  QDir().mkdir(newpath);
  QDir().mkdir(newpath + "/males");
  QDir().mkdir(newpath + "/females");
  QDir().mkdir(newpath + "/not recognized");
  QDir().mkdir(newpath + "/not recognized");
  QDir().mkdir(newpath + "/both");
  on_recognize_B_clicked();
  auto list = model->get_paths();
  int i = 0;
  auto it = model->get_items().begin();
  foreach (QString oldpath, list) {
    bool is_male = it.value()->contains(MALE);
    bool is_female = it.value()->contains(FEMALE);
    QString subpath;
    if (is_male && is_female) {
      subpath = "/both/";
    } else if (is_male) {
      subpath = "/males/";
    } else if (is_female) {
      subpath = "/females/";
    } else {
      subpath = "/not recognized/";
    }
    it++;

    oldpath.replace("~", home);
    if (QFile::copy(oldpath, newpath + subpath + oldpath.split("/").last())) {
      if (facecope->settings->getCut_files()) {
        QFile::remove(oldpath);
      }
      qDebug() << "copied";
    }
  }
}

void FWorkingWidget::on_clear_B_clicked() { model_proxy->clear(); }

void FWorkingWidget::on_show_woman(bool enable) {
  emit signal_images_changed();
}

void FWorkingWidget::on_show_man(bool enable) { emit signal_images_changed(); }

void FWorkingWidget::on_showAll_RB_clicked() {
  model_proxy->setShow_recognized(false);
  model_proxy->setShow_unrecognized(false);
  model_proxy->apply();
  emit signal_images_changed();
}
