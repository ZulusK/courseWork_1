#include "FSettingsWidget.h"
#include "ui_FSettingsWidget.h"
#include <QFileDialog>
FSettingsWidget::FSettingsWidget(Settings &settings, QWidget *parent)
    : QWidget(parent), ui(new Ui::FSettingsWidget) {
  this->settings = &settings;
  ui->setupUi(this);
  showSettings();
}
void FSettingsWidget::showSettings() {
  if (settings->getCascade_type() == USE_LBP) {
    ui->lbp_RB->setChecked(true);
  } else {
    ui->haar_RB->setChecked(true);
  }
  ui->cutFiles_CB->setChecked(settings->getCut_files());
  ui->learnGender_CB->setChecked(settings->getLearn_gender());
  ui->skipUnrecognized_CB->setChecked(settings->getSkip_unRecognized());
  ui->learRecognized_CB->setChecked(settings->getLearn_recognized());
  ui->steps_SB->setValue(settings->getSteps_of_detection());
  ui->steps_SL->setValue(settings->getSteps_of_detection());
  ui->threahold_SB->setValue(settings->getThreahold() / 100);
  ui->threahold_SL->setValue(settings->getThreahold() / 100);
}

FSettingsWidget::~FSettingsWidget() { delete ui; }

void FSettingsWidget::on_haar_RB_clicked() {
  settings->setCascade_type(USE_HAAR);
}

void FSettingsWidget::on_lbp_RB_clicked() {
  settings->setCascade_type(USE_LBP);
}

void FSettingsWidget::on_cutFiles_CB_clicked() {
  this->settings->setCut_files(ui->cutFiles_CB->isChecked());
}

void FSettingsWidget::on_selectOutDir_B_clicked() {

  QString dirName = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "~/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (dirName.length() > 0)
    settings->setOutput_path(dirName + ((dirName.endsWith("/")) ? "" : "/"));
}

void FSettingsWidget::on_threahold_SB_valueChanged(double arg1) {
  ui->threahold_SL->setValue(arg1);
  settings->setThreahold(arg1 * 100);
}

void FSettingsWidget::on_threahold_SL_sliderMoved(int position) {
  ui->threahold_SB->setValue(position);
  settings->setThreahold(position * 100);
}

void FSettingsWidget::on_steps_SL_sliderMoved(int position) {
  ui->steps_SB->setValue(position);
  settings->setSteps_of_detection(position);
}

void FSettingsWidget::on_steps_SB_valueChanged(int arg1) {
  ui->steps_SL->setValue(arg1);
  settings->setSteps_of_detection(arg1);
}

void FSettingsWidget::on_import_B_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, QString("Open file"), settings->getSave_settings_path(),
      "Settings (settings.fcp);;");
  settings->load(fileName);
  showSettings();
}

void FSettingsWidget::on_export_B_clicked() {
  QString dirName = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), settings->getSave_settings_path(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  settings->save(dirName + ((dirName.endsWith("/")) ? "" : "/"));
}

void FSettingsWidget::on_learRecognized_CB_clicked() {
  settings->setLearn_recognized(ui->learRecognized_CB->isChecked());
}

void FSettingsWidget::on_skipUnrecognized_CB_clicked() {
  settings->setSkip_unRecognized(ui->skipUnrecognized_CB->isChecked());
}

void FSettingsWidget::on_learnGender_CB_clicked() {
  settings->setLearn_gender(ui->learnGender_CB->isChecked());
}
