#include "FileBrowserWindow.h"
#include "ui_FileBrowserWindow.h"
#include <QFileIconProvider>
#include <iostream>

FileBrowserWindow::FileBrowserWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FileBrowserWindow) {
  ui->setupUi(this);
  this->setCentralWidget(ui->splitter);
  QThreadPool::globalInstance()->setMaxThreadCount(1);
  model = new QFileSystemModel(this);
  model->setRootPath("/");

  filesmodel = new QStandardItemModel(this);
  ui->treeView->setModel(model);
  ui->listView->setModel(filesmodel);
  ui->treeView->setRootIndex(model->index("/home/zulus/"));
  ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
  connect(this, SIGNAL(UpdateItem(int, QImage)), SLOT(setThumbs(int, QImage)));

  QSize listIconSize=ui->listView->iconSize();
ui->listView->setIconSize(QSize(listIconSize.width()/3,listIconSize.width()*4/9));
  running = false;
}

FileBrowserWindow::~FileBrowserWindow() { delete ui; }

void FileBrowserWindow::on_treeView_clicked(const QModelIndex &index) {
  filesmodel->clear();
  running = false;
  thread.waitForFinished();
  QDir dir(model->filePath(ui->treeView->currentIndex()));
  QFileInfoList filesList = dir.entryInfoList(QStringList() << "*.jpg"
                                                            << "*.jpeg"
                                                            << "*.tif"
                                                            << "*.png"
                                                            << "*.gif"
                                                            << "*.bmp",
                                              QDir::Files);
  int filesCount = filesList.size();
  QFileIconProvider fileIcon;
  QIcon placeHolder = fileIcon.icon(QFileIconProvider::File);

  for (int i = 0; i < filesCount; i++)
    filesmodel->setItem(i, new QStandardItem(placeHolder, filesList[i].baseName()));
  running = true;
  thread = QtConcurrent::run(this, &FileBrowserWindow::List, filesList,
                             ui->listView->iconSize());
}

void FileBrowserWindow::List(QFileInfoList filesList, QSize size) {
  int filesCount = filesList.size();
  for (int i = 0; running && i < filesCount; i++) {
    QImage originalImage(filesList[i].filePath());
    if (!originalImage.isNull()) {
      QImage scaledImage =
          originalImage.scaled(size, Qt::AspectRatioMode::KeepAspectRatio);
      if (!running)
        return;
      emit UpdateItem(i, scaledImage);
    }
  }
}

void FileBrowserWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
}

void FileBrowserWindow::setThumbs(int index, QImage img) {
  QIcon icon = QIcon(QPixmap::fromImage(img));
  QStandardItem *item = filesmodel->item(index);
  filesmodel->setItem(index, new QStandardItem(icon, item->text()));
}
