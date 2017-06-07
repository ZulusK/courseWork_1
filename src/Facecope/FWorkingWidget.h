#ifndef FWORKINGWIDGET_H
#define FWORKINGWIDGET_H

#include <FImageListModel.h>
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
#include <QtConcurrent>
namespace Ui {
class FWorkingWidget;
}

class FWorkingWidget : public QWidget {
  Q_OBJECT

public:
  explicit FWorkingWidget(QMap<QString, QImage> *images, QWidget *parent = 0);
  ~FWorkingWidget();

signals:
  void UpdateItem(QString, QImage);

private slots:
  void addImages(QList<QUrl> urls, QSize size);
  void setThumbs(QString index, QImage img);
  void dropEvent(QDropEvent *e);
  void dragEnterEvent(QDragEnterEvent *e);


private:
  Ui::FWorkingWidget *ui;
  QStandardItemModel *list_model;
  QFuture<void> thread;
};

#endif // FWORKINGWIDGET_H
