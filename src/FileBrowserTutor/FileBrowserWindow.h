#ifndef FILEBROWSERWINDOW_H
#define FILEBROWSERWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
namespace Ui {
class FileBrowserWindow;
}

class FileBrowserWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FileBrowserWindow(QWidget *parent = 0);
  ~FileBrowserWindow();

private:
  Ui::FileBrowserWindow *ui;
  QFileSystemModel *dirModel;
  QFileSystemModel *fileModel;
};

#endif // FILEBROWSERWINDOW_H
