#include "FileBrowserWindow.h"
#include "ui_FileBrowserWindow.h"

FileBrowserWindow::FileBrowserWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FileBrowserWindow) {
  ui->setupUi(this);
  QString sPath = "~/";
  dirModel = new QFileSystemModel(this);
  dirModel->setRootPath(sPath);
  ui->dirTree->setModel(dirModel);
}

FileBrowserWindow::~FileBrowserWindow() { delete ui; }
