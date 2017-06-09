#include "FMainWindow.h"
#include "ui_FMainWindow.h"
#include <FFaceRecognizer.h>
#include <FHelpWidget.h>
#include <FSettingsWidget.h>
#include <FWorkingWidget.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
enum { HELP, WORK, BACK, SETTINGS };

FMainWindow::FMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FMainWindow) {
  ui->setupUi(this);
  createWidgets();
  connect_signals();
  start();
}
void FMainWindow::connect_signals() {
  connect(ui->action_open, SIGNAL(triggered()), this, SLOT(open_files()));
  connect(ui->action_help, SIGNAL(triggered()), this, SLOT(show_widget()));
  connect(ui->action_back, SIGNAL(triggered()), this, SLOT(show_widget()));
  connect(ui->action_settings, SIGNAL(triggered()), this, SLOT(show_widget()));
  connect(ui->action_trash, SIGNAL(triggered()), image_model,
          SLOT(slot_clear()));
  connect(ui->action_delete, SIGNAL(triggered()), working_widget,
          SLOT(slot_remove_selected()));
  connect(ui->action_run, SIGNAL(triggered()), working_widget,
          SLOT(on_recognize_B_clicked()));
  connect(ui->action_man, SIGNAL(triggered(bool)), working_widget,
          SLOT(on_show_man(bool)));
  connect(ui->action_woman, SIGNAL(triggered(bool)), working_widget,
          SLOT(on_show_woman(bool)));
  connect(ui->action_save, SIGNAL(triggered()), working_widget,
          SLOT(on_save_B_clicked()));
  connect(ui->action_webcam, SIGNAL(triggered()), this,
          SLOT(slot_recognize_webcam()));
}

FMainWindow::~FMainWindow() {
  delete ui;
  delete working_widget;
  delete image_model;
  delete facecope.detector;
  facecope.recognizer_face->save(
      facecope.settings->getRecognizer_path().toStdString());
  facecope.recognizer_gender->save(
      facecope.settings->getRecognizer_gender_path().toStdString());
  delete facecope.database;
  delete facecope.settings;
  delete facecope.recognizer_face;
  delete facecope.recognizer_gender;
}

void FMainWindow::createWidgets() {
  this->facecope.settings = new Settings();
  this->facecope.database = new FDatabaseDriver(settings);
  this->facecope.database->get_user(1);
  this->facecope.detector =
      new FFaceDetector(std::string(RESOURCE_PATH) + "cascades/face_haar.xml",
                        std::string(RESOURCE_PATH) + "cascades/face_lbp.xml",
                        std::string(RESOURCE_PATH) + "cascades/eye_haar.xml");

  this->facecope.recognizer_face = new FFaceRecognizer();
  this->facecope.recognizer_gender = new FFaceRecognizer();
  this->facecope.recognizer_face->load(
      facecope.settings->getRecognizer_path().toStdString());
  this->facecope.recognizer_gender->load(
      facecope.settings->getRecognizer_gender_path().toStdString());

  this->image_model = new FMainFacecopeModel(facecope, this);
  this->working_widget = new FWorkingWidget(facecope, image_model, this);
}

void FMainWindow::start() {
  if (centralWidget() != working_widget) {
    setCentralWidget(working_widget);
  }
}

void FMainWindow::open_files() {
  QStringList filesNames = QFileDialog::getOpenFileNames(
      this, QString("Open file"), ".", "Images (*.png  *.jpg);;");
  working_widget->slot_add_images(filesNames);
}
void FMainWindow::show_widget() {
  auto sender = QObject::sender();
  if (sender == ui->action_help) {
    working_widget->setParent(NULL);
    setCentralWidget(new FHelpWidget(this));
  } else if (sender == ui->action_settings) {
    working_widget->setParent(NULL);
    setCentralWidget(new FSettingsWidget(settings, this));
  } else {
    if (centralWidget() != working_widget) {
      setCentralWidget(working_widget);
    }
  }
}

void FMainWindow::slot_recognize_webcam() {
  QMessageBox::StandardButton reply;
  int gender = -1;
  reply = QMessageBox::question(this, "Choose gender", "Its will be a man?",
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    gender = MALE;
  } else {
    gender = FEMALE;
  }
  this->hide();

  learnNewHuman(facecope, facecope.database->getNextId(), gender);
  this->show();
}
