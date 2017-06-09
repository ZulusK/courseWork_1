#ifndef FIMAGESHOWDIALOG_H
#define FIMAGESHOWDIALOG_H
#include <FDatabaseDriver.h>
#include <FFaceModel.h>
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
  explicit FImageShowDialog(FDatabaseDriver &database, FImage &image,
                            Settings &settings, QWidget *parent = 0);
  ~FImageShowDialog();

private slots:
  void on_splitter_splitterMoved(int pos, int index);

  void on_size_slider_sliderMoved(int position);

private:
  Ui::FImageShowDialog *ui;
  FImage *f_image;
  Settings *settings;
  FImageDrawAreaWidget *draw_area;
  FFaceModel *model;
  FDatabaseDriver *database;
};

#endif // FIMAGESHOWDIALOG_H
