#include "dialoglistview.h"
#include "ui_dialoglistview.h"
#include <mylistmodel.h>
DialogListView::DialogListView(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogListView) {
  ui->setupUi(this);

  QStringList list;
  list << "a"
       << "b"
       << "c"
       << "d";
  MyListModel *model = new MyListModel(list);
  QListView *view = new QListView;
  ui->listView->setModel(model);
}

DialogListView::~DialogListView() { delete ui; }

void DialogListView::on_changeBtn_clicked() {}

void DialogListView::on_removeBtn_clicked() {}

void DialogListView::on_addBtn_clicked() {}
