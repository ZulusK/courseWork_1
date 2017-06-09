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

  void on_list_view_doubleClicked(const QModelIndex &index);

  void on_selecthuman_CB_currentIndexChanged(int index);

  void on_show_rec_RB_clicked();

  void on_show_UR_RB_clicked();

  void on_detect_B_clicked();

  void on_recognize_B_clicked();

  void on_save_B_clicked();

  void on_clear_B_clicked();

  void on_sizeSlider_sliderMoved(int position);
  void on_show_woman(bool enable);
  void on_show_man(bool enable);

private:
  void setUp();
  Ui::FWorkingWidget *ui;
  FImageThumbModel *model;
  FImageProxyModel *model_proxy;
  QCompleter *completer;
  Settings *settings;
};

#endif // FWORKINGWIDGET_H
