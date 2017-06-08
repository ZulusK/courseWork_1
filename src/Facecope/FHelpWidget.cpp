#include "FHelpWidget.h"
#include "ui_FHelpWidget.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
FHelpWidget::FHelpWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::FHelpWidget) {
  QFile file(":/helpText.html");
  QString text = "Not loaded, check file \"res/helpText.html\"";
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in(&file);
    text = in.readAll();
  } else {
    QMessageBox::information(0, "info", file.errorString());
  }
  ui->setupUi(this);
  ui->textBrowser->setText(text);
}

FHelpWidget::~FHelpWidget() { delete ui; }
