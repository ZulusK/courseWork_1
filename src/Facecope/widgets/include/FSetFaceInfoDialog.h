/** @file
    @brief defines dialog for editing labels of face
*/
#ifndef FSETFACEINFODIALOG_H
#define FSETFACEINFODIALOG_H

#include <FacecopeTypes.h>
#include <QDialog>
#include <QImage>
namespace Ui {
class FSetFaceInfoDialog;
}

class FSetFaceInfoDialog : public QDialog {
  Q_OBJECT

public:
  explicit FSetFaceInfoDialog(Facecope &facecope, FFace &face, FImage &f_image,
                              QWidget *parent = 0);
  ~FSetFaceInfoDialog();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::FSetFaceInfoDialog *ui;
  Facecope *facecope;
  FFace *face;
  FImage *f_image;
};

#endif // FSETFACEINFODIALOG_H
