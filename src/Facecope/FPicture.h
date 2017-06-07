#ifndef FPICTURE_H
#define FPICTURE_H

#include <FMainWindow.h>
#include <ImageProcessing/FImage.h>
#include <ImageProcessing/Facecope.h>
#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QWidget>
namespace Ui {
class FPicture;
}

class FPicture : public QWidget {
  Q_OBJECT

public:
  explicit FPicture(const QString &imagePath, QWidget *parent = NULL);
  explicit FPicture(FImage *image, QWidget *parent = NULL);
  ~FPicture();
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;
  void set_size(int width, int height);
  void paintEvent(QPaintEvent *event) override;
  void set_image(FImage *image);
  static void toQImage(FImage &f_image, QImage &q_image);
private:
  void draw_faceArea(QPainter &painter, long id);
  void draw_image(QPainter &painter);

private:
  Ui::FPicture *ui;
  cv::Size f_image_size;
  FImage *f_image;
  bool draw_person;
  QImage q_image;
};

#endif // FPICTURE_H
