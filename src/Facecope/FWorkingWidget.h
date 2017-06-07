#ifndef FWORKINGWIDGET_H
#define FWORKINGWIDGET_H

#include <FImageThumbModel.h>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QStandardItemModel>
#include <QWidget>

#include <QFileInfoList>
#include <QFuture>
#include <QIcon>
#include <QImage>
#include <QList>
#include <QSize>
#include <QUrl>

namespace Ui {
class FWorkingWidget;
}

class FWorkingWidget : public QWidget {
  Q_OBJECT

public:
  explicit FWorkingWidget(QMap<QString, QImage> *images, QWidget *parent = 0);
  ~FWorkingWidget();

signals:
  void UpdateItem(const QString &path);

private slots:
  void addImages(const QList<QUrl> &urls);
  void dropEvent(QDropEvent *e);
  void dragEnterEvent(QDragEnterEvent *e);

  void on_horizontalSlider_sliderMoved(int position);

private:
  void addImagesToModel(const QString &path);

private:
  Ui::FWorkingWidget *ui;
  FImageThumbModel *list_model;
};

#endif // FWORKINGWIDGET_H
