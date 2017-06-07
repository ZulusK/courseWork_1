#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <FImageThumbModel.h>
#include <QImage>
#include <QMainWindow>
#include <QMap>
#include <QString>

<<<<<<< HEAD:Demo/FMainWindow.h
=======
enum { START_MENU, FILE_BROWSING, IMAGE_EDIT };
>>>>>>> f703f6ca650b4491287f815b314b1755944719c1:src/Facecope/include/FMainWindow.h
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
