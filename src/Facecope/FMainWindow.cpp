#include "FMainWindow.h"
#include "ui_FMainWindow.h"

FMainWindow::FMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FMainWindow) {
  ui->setupUi(this);
  createWidgets();
  start();
}

FMainWindow::~FMainWindow() { delete ui; }
void FMainWindow::createWidgets() {
  this->working_widget = new FWorkingWidget(&loaded_images, this);
}
void FMainWindow::start() { setCentralWidget(working_widget); }
