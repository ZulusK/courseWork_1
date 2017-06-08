#include "FMainWindow.h"
#include "ui_FMainWindow.h"
#include <FHelpWidget.h>
#include <FWorkingWidget.h>
#include <QFileDialog>
#include <QProgressDialog>
enum { HELP, WORK, BACK };
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
}

FMainWindow::~FMainWindow() {
  delete ui;
  delete image_model;
}

void FMainWindow::createWidgets() {
  this->image_model = new FImageThumbModel(this);
  this->working_widget = new FWorkingWidget(image_model, this);
}

void FMainWindow::start() {
  if (centralWidget() != working_widget) {
    setCentralWidget(working_widget);
  }
}

void FMainWindow::open_files() {
  QStringList filesNames = QFileDialog::getOpenFileNames(
      this, QString("Open file"), ".", "Images (*.png  *.jpg);;");
  working_widget->addImages(filesNames);
}
void FMainWindow::show_widget() {
  auto sender = QObject::sender();
  if (sender == ui->action_help) {
    working_widget->setParent(NULL);
    setCentralWidget(new FHelpWidget(this));
  } else {
    if (centralWidget() != working_widget) {
      setCentralWidget(working_widget);
    }
  }
}
