#include <QApplication>
#include <QListView>
#include <dialoglistview.h>
#include <mylistmodel.h>
int main(int argc, char **argv) {
  QApplication app(argc, argv);
  DialogListView dialog;
  return dialog.exec();
}
