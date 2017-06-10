/** @file
    @brief defines dialog for lavel viewing and editing
*/
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
  explicit FImageShowDialog(Facecope &facecope, FImage &image,
                            QWidget *parent = 0);
  ~FImageShowDialog();

private slots:
  void on_splitter_splitterMoved(int pos, int index);

  void on_size_slider_sliderMoved(int position);

  void on_tableView_doubleClicked(const QModelIndex &index);

private:
  Ui::FImageShowDialog *ui;
  FImage *f_image;
  FImageDrawAreaWidget *draw_area;
  FFaceModel *model;
  Facecope *facecope;
};

#endif // FIMAGESHOWDIALOG_H
