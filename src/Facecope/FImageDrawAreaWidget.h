#ifndef FIMAGEDRAWAREAWIDGET_H
#define FIMAGEDRAWAREAWIDGET_H

#include <FImage.h>
#include <QWidget>
#include <Settings.h>
namespace Ui {
class FImageDrawAreaWidget;
}

class FImageDrawAreaWidget : public QWidget {
  Q_OBJECT

public:
  explicit FImageDrawAreaWidget(FImage &image, Settings &settings,
                                QWidget *parent = 0);
  ~FImageDrawAreaWidget();
  QSize minimumSizeHint() const override;

  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Ui::FImageDrawAreaWidget *ui;
  FImage *f_image;
  Settings *settings;
};

#endif // FIMAGEDRAWAREAWIDGET_H
