#ifndef FIMAGESHOWDIALOG_H
#define FIMAGESHOWDIALOG_H

#include <FImage.h>
#include <FImageDrawAreaWidget.h>
#include <QDialog>
#include <Settings.h>
namespace Ui {
class FImageShowDialog;
}

class FImageShowDialog : public QDialog {
  Q_OBJECT

public:
  explicit FImageShowDialog(FImage &image, Settings &settings,
                            QWidget *parent = 0);
  ~FImageShowDialog();

private slots:
  void on_splitter_splitterMoved(int pos, int index);

private:
  Ui::FImageShowDialog *ui;
  FImage *f_image;
  Settings *settings;
  FImageDrawAreaWidget *draw_area;
};

#endif // FIMAGESHOWDIALOG_H
