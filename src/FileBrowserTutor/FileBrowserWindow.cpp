#include "FileBrowserWindow.h"
#include "ui_FileBrowserWindow.h"
#include <iostream>
FileBrowserWindow::FileBrowserWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FileBrowserWindow) {
  ui->setupUi(this);
  QString sPath = "/home/zulus";
  dirModel = new QFileSystemModel(this);
  dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
  dirModel->setRootPath(sPath);
  ui->dirTree->setModel(dirModel);

  fileModel = new QFileSystemModel(this);
  fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
  fileModel->setRootPath(sPath);
  ui->dirList->setModel(fileModel);
}

FileBrowserWindow::~FileBrowserWindow() { delete ui; }

void FileBrowserWindow::on_dirTree_clicked(const QModelIndex &index) {
  QString sPath = dirModel->fileInfo(index).absoluteFilePath();
  std::cout << sPath.toStdString() << std::endl;
  ui->dirList->setRootIndex(fileModel->setRootPath(sPath));
}
