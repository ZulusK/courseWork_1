/** @file
    @brief defines settings-widget
*/
#ifndef FSETTINGSWIDGET_H
#define FSETTINGSWIDGET_H

#include <QWidget>
#include <Settings.h>

namespace Ui {
class FSettingsWidget;
}

class FSettingsWidget : public QWidget {
  Q_OBJECT

public:
  explicit FSettingsWidget(Settings &settings, QWidget *parent = 0);
  ~FSettingsWidget();

private slots:
  void on_haar_RB_clicked();

  void on_lbp_RB_clicked();

  void on_cutFiles_CB_clicked();

  void on_selectOutDir_B_clicked();

  void on_threahold_SB_valueChanged(double arg1);

  void on_threahold_SL_sliderMoved(int position);

  void on_steps_SL_sliderMoved(int position);

  void on_steps_SB_valueChanged(int arg1);

  void on_import_B_clicked();

  void on_export_B_clicked();

  void on_learRecognized_CB_clicked();

  void on_skipUnrecognized_CB_clicked();

  void on_learnGender_CB_clicked();

private:
  void showSettings();

private:
  Ui::FSettingsWidget *ui;
  Settings *settings;
};

#endif // FSETTINGSWIDGET_H
