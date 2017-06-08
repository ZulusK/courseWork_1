#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <FFaceDetector.h>
#include <FImageThumbModel.h>
#include <FWorkingWidget.h>
#include <FacecopeTypes.h>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QStringList>
#include <QUrl>
#include <Settings.h>
#define  RESOURCE_PATH "../../res/"
namespace Ui {
class FMainWindow;
}

class FMainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FMainWindow(QWidget *parent = 0);
  ~FMainWindow();
signals:
  void signal_openFileDialog();
  void signal_showHelp();
  void signal_getBack();
  void load_files(const QStringList &paths);
  void load_files(const QList<QUrl> &urls);

protected slots:
  void open_files();
  void show_widget();

private:
  void createWidgets();
  void start();
  void connect_signals();
  Ui::FMainWindow *ui;
  QMap<QString, QImage> loaded_images;
  bool is_loading_running;
  FImageThumbModel *image_model;
  FWorkingWidget *working_widget;
  Settings settings;
  FacecopeProcessors processors;
};

#endif // FMAINWINDOW_H
