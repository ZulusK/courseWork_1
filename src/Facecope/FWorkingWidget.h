#ifndef FWORKINGWIDGET_H
#define FWORKINGWIDGET_H

#include <FImageProxyModel.h>
#include <FImageThumbModel.h>
#include <QCompleter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfoList>
#include <QImage>
#include <QList>
#include <QMutex>
#include <QSize>
#include <QUrl>
#include <QWidget>
#include <Settings.h>
namespace Ui {
class FWorkingWidget;
}

class FWorkingWidget : public QWidget {
  Q_OBJECT

public:
  explicit FWorkingWidget(Settings &settings, FImageThumbModel *model,
                          QWidget *parent = 0);
  ~FWorkingWidget();

signals:
  void signal_updateItem(const QString &path);
  void signal_images_changed();
  void signal_load_images(const QList<QUrl> &urls);
  void signal_load_images(const QStringList &urls);
  void signal_detect_face(int row);

public slots:
  void addImages(const QStringList &urls);
  void addImages(const QList<QUrl> &urls);
  void remove_selected();

private slots:
  void dropEvent(QDropEvent *e);
  void dragEnterEvent(QDragEnterEvent *e);
  void on_horizontalSlider_sliderMoved(int position);
  void on_list_view_doubleClicked(const QModelIndex &index);
  void on_horizontalSlider_2_valueChanged(int value);
  void on_spinBox_valueChanged(int arg1);

private:
  void setUp();
  Ui::FWorkingWidget *ui;
  FImageThumbModel *model;
  FImageProxyModel *model_proxy;
  QCompleter *completer;
  Settings *settings;
};

#endif // FWORKINGWIDGET_H
