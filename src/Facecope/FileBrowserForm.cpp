#include "FileBrowserForm.h"
#include "ui_FileBrowserForm.h"
#include <QDebug>
#include <QString>
FileBrowserForm::FileBrowserForm(FMainWindow &facecope)
    : QWidget(&facecope), ui(new Ui::FileBrowserForm) {
  ui->setupUi(this);
  setAcceptDrops(true);
  QThreadPool::globalInstance()->setMaxThreadCount(1);
  filesmodel = new FPicruresModel(this);
  ui->workingDir_view->setModel(filesmodel);
  filesmodel->add(QString::fromStdString("/home/zulus/Projects/progbase3/res/danil/Image0.jpg"));
  filesmodel->add(QString::fromStdString("/home/zulus/Projects/progbase3/res/danil/Image1.jpg"));
  filesmodel->add(QString::fromStdString("/home/zulus/Projects/progbase3/res/danil/Image2.jpg"));
  filesmodel->add(QString::fromStdString("/home/zulus/Projects/progbase3/res/danil/Image3.jpg"));
  filesmodel->add(QString::fromStdString("/home/zulus/Projects/progbase3/res/danil/Image4.jpg"));
}

FileBrowserForm::~FileBrowserForm() { delete ui; }

void FileBrowserForm::dragEnterEvent(QDragEnterEvent *e) {}

void FileBrowserForm::dropEvent(QDropEvent *e) {}
