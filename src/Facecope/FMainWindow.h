#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <FIcon.h>
#include <FImageThumbModel.h>
#include <FWorkingWidget.h>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QStringList>
#include <QUrl>
#include <QtConcurrent>
namespace Ui {
class FMainWindow;
}

class FMainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FMainWindow(QWidget *parent = 0);
  ~FMainWindow();
protected slots:
  void open_files();

private:
  void createWidgets();
  void start();

  Ui::FMainWindow *ui;
  FWorkingWidget *working_widget;
  QMap<QString, QImage> loaded_images;
  bool is_loading_running;
  FImageThumbModel *image_model;
  QFuture<void> thread;
};

#endif // FMAINWINDOW_H
