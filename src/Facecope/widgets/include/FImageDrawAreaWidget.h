#ifndef FIMAGEDRAWAREAWIDGET_H
#define FIMAGEDRAWAREAWIDGET_H

#include <FacecopeTypes.h>
#include <QPen>
#include <QWidget>
#include<FImage.h>
#include <Settings.h>
namespace Ui {
class FImageDrawAreaWidget;
}

class FImageDrawAreaWidget : public QWidget {
  Q_OBJECT

public:
  explicit FImageDrawAreaWidget(Facecope &facecope, FImage &image, QWidget *parent = 0);
  ~FImageDrawAreaWidget();
  QSize minimumSizeHint() const override;

  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Ui::FImageDrawAreaWidget *ui;
  FImage *f_image;
  Facecope *facecope;
  Settings *settings;
  QPen recognized_male;
  QPen recognized_female;
  QPen unrecognized;
};

#endif // FIMAGEDRAWAREAWIDGET_H
