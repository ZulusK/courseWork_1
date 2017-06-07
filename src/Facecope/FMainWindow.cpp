#include "FMainWindow.h"
#include "ui_FMainWindow.h"
#include <QProgressDialog>
FMainWindow::FMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FMainWindow) {
  ui->setupUi(this);
  createWidgets();
  start();
}

FMainWindow::~FMainWindow() {
  delete ui;
  delete image_model;
}

void FMainWindow::createWidgets() {
  this->image_model = new FImageThumbModel();
  this->working_widget = new FWorkingWidget(image_model, this);
}

void FMainWindow::start() { setCentralWidget(working_widget); }

