#ifndef FWORKINGWIDGET_H
#define FWORKINGWIDGET_H

#include <FImageThumbModel.h>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfoList>
#include <QImage>
#include <QList>
#include <QSize>
#include <QUrl>
#include <QWidget>
namespace Ui {
class FWorkingWidget;
}

class FWorkingWidget : public QWidget {
  Q_OBJECT

public:
  explicit FWorkingWidget(FImageThumbModel *model, QWidget *parent = 0);
  ~FWorkingWidget();

signals:
  void UpdateItem(const QString &path);
  void images_changed();
  void images_added(const QList<QUrl> &urls);
private slots:
  void addImages(const QList<QUrl> &urls);
  void dropEvent(QDropEvent *e);
  void dragEnterEvent(QDragEnterEvent *e);
  void on_horizontalSlider_sliderMoved(int position);

private:
  Ui::FWorkingWidget *ui;
  FImageThumbModel *model;
};

#endif // FWORKINGWIDGET_H
