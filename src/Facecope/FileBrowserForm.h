#ifndef FILEBROWSERFORM_H
#define FILEBROWSERFORM_H

#include <FMainWindow.h>
#include <FPicruresModel.h>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfoList>
#include <QFuture>
#include <QIcon>
#include <QImage>
#include <QMainWindow>
#include <QSize>
#include <QStringList>
#include <QWidget>
#include <QtConcurrent>
namespace Ui {
class FileBrowserForm;
}

class FileBrowserForm : public QWidget {
  Q_OBJECT

public:
  explicit FileBrowserForm(FMainWindow &facecope);
  ~FileBrowserForm();

protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dropEvent(QDropEvent *event);
  void List(QFileInfoList fileList, QSize size);
  void setThumbs(int index, QImage img);
//  void resizeEvent(QResizeEvent *event);

private:
  Ui::FileBrowserForm *ui;
  QStringList loadedImages;
  FMainWindow *facecope;
  FPicruresModel *filesmodel;
  QFuture<void> thread;
  bool running;
};

#endif // FILEBROWSERFORM_H
