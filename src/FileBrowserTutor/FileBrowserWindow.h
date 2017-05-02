#ifndef FILEBROWSERWINDOW_H
#define FILEBROWSERWINDOW_H

#include <QFileInfoList>
#include <QFileSystemModel>
#include <QFuture>
#include <QIcon>
#include <QImage>
#include <QMainWindow>
#include <QSize>
#include <QStandardItemModel>
#include <QtConcurrent>

namespace Ui {
class FileBrowserWindow;
}

class FileBrowserWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FileBrowserWindow(QWidget *parent = 0);
  ~FileBrowserWindow();

signals:
  void UpdateItem(int, QImage);
private slots:
  void List(QFileInfoList fileList, QSize size);
  void setThumbs(int index, QImage img);
  void on_treeView_clicked(const QModelIndex &index);

private:
  Ui::FileBrowserWindow *ui;
  QFileSystemModel *model;
  QStandardItemModel *filesmodel;
  QFuture<void> thread;
  bool running;
};

#endif // FILEBROWSERWINDOW_H
