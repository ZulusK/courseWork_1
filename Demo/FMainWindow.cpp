#include "FMainWindow.h"
#include "ui_FMainWindow.h"

FMainWindow::FMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FMainWindow) {
  ui->setupUi(this);
  this->loaded_images[QString("~/Projects/progbase3/res/people.jpg")] =
      QImage("/home/zulus/Projects/progbase3/res/people.jpg");
  this->model = new FImageThumbModel(&loaded_images, this);
  ui->listView->setModel(model);
  ui->listView->setIconSize(QSize(300,300));
}

FMainWindow::~FMainWindow() {
  delete ui;
  delete model;
}
