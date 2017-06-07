#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <FImageThumbModel.h>
#include <QImage>
#include <QMainWindow>
#include <QMap>
#include <QString>

namespace Ui {
class FMainWindow;
}

class FMainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FMainWindow(QWidget *parent = 0);
  ~FMainWindow();

private:
  Ui::FMainWindow *ui;

  QMap<QString, QImage> loaded_images;
  FImageThumbModel *model;
};

#endif // FMAINWINDOW_H
