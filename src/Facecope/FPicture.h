#ifndef FPICTURE_H
#define FPICTURE_H

#include <FMainWindow.h>
#include <ImageProcessing/FImage.h>
#include <ImageProcessing/Facecope.h>
#include <QWidget>
namespace Ui {
class FPicture;
}

class FPicture : public QWidget {
  Q_OBJECT

public:
  explicit FPicture(const QString &imagePath, FMainWindow *parent);
  ~FPicture();
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Ui::FPicture *ui;
  FImage *f_image;
  uchar *image_data;
  FMainWindow * parent;
};

#endif // FPICTURE_H
