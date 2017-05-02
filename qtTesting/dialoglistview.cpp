#include "dialoglistview.h"
#include "ui_dialoglistview.h"
#include <QDir>
#include <QFileSystemModel>
#include <QString>
#include <mylistmodel.h>
DialogListView::DialogListView(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogListView) {
  ui->setupUi(this);

  //  QStringList list;
  //  list << "a"
  //       << "b"
  //       << "c"
  //       << "d";
  //  MyListModel *model = new MyListModel(list);
  //  QListView *view = new QListView;
  //  ui->listView->setModel(model);
  QFileSystemModel *std = new QFileSystemModel();
  std->setRootPath(QDir::currentPath());
  // to arrange the items
  ui->listView->setUniformItemSizes(true);
  // join the model to the listView
  ui->listView->setModel(std);
}

DialogListView::~DialogListView() { delete ui; }

void DialogListView::on_changeBtn_clicked() {}

void DialogListView::on_removeBtn_clicked() {}

void DialogListView::on_addBtn_clicked() {}

void DialogListView::on_lineEdit_textChanged(const QString &arg1) {
  QFileSystemModel *std = (QFileSystemModel *)ui->listView->model();
  std->setRootPath(QDir::homePath());
}
