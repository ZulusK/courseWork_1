#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <FIcon.h>
#include <FWorkingWidget.h>
#include <QMainWindow>
#include <QMap>
namespace Ui {
class FMainWindow;
}

class FMainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FMainWindow(QWidget *parent = 0);
  ~FMainWindow();

private:
  void createWidgets();
  void start();
  Ui::FMainWindow *ui;
  FWorkingWidget *working_widget;
  QMap<QString, QImage> loaded_images;
};

#endif // FMAINWINDOW_H
