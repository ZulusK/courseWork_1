#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <QMainWindow>

enum { START_MENU, FILE_BROWSING, IMAGE_EDIT };
namespace Ui {
class FMainWindow;
}

class FMainWindow : public QMainWindow {
  Q_OBJECT
private:
  void create_toolBar();

public:
  explicit FMainWindow(QWidget *parent = 0);
  ~FMainWindow();
signals:
  void signal_setCentralWidget(QWidget *sender, int type);
public slots:
  void on_setCentralWidget(QWidget *sender, int type);

private:
  Ui::FMainWindow *ui;
};

#endif // FMAINWINDOW_H
