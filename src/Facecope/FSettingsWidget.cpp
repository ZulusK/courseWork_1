#include "FSettingsWidget.h"
#include "ui_FSettingsWidget.h"

FSettingsWidget::FSettingsWidget(Settings &settings, QWidget *parent)
    : QWidget(parent), ui(new Ui::FSettingsWidget) {
  this->settings = &settings;
  ui->setupUi(this);
}

FSettingsWidget::~FSettingsWidget() { delete ui; }
