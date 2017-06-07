#include "ui_FMainWindow.h"
#include <FMainWindow.h>
#include <FPicture.h>
#include <FileBrowserForm.h>
#include <StartMenuForm.h>
FMainWindow::FMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FMainWindow) {
  ui->setupUi(this);
  create_toolBar();
  this->setCentralWidget(new FileBrowserForm(*this));
  connect(this, SIGNAL(signal_setCentralWidget(QWidget *, int)), this,
          SLOT(on_setCentralWidget(QWidget *, int)));
}

FMainWindow::~FMainWindow() { delete ui; }

void FMainWindow::create_toolBar() {
  ui->menuBar->addMenu("&Facecope");
  ui->menuBar->addMenu(qApp->translate("FMainWindow", "&File"));
}

void FMainWindow::on_setCentralWidget(QWidget *sender, int type) {
  switch (type) {
  case IMAGE_EDIT:
    this->setCentralWidget(new FPicture(
        QString("/home/zulus/Projects/progbase3/res/people3.jpg"), this));

    break;
  case FILE_BROWSING:
    this->setCentralWidget(new FileBrowserForm(*this));
    break;
  default:
    break;
  }
  delete sender;
}
