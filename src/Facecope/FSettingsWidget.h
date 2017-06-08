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

private:
  Ui::FSettingsWidget *ui;
  Settings * settings;
};

#endif // FSETTINGSWIDGET_H
