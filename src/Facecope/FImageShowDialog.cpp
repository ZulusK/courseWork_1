#include "FImageShowDialog.h"
#include "ui_FImageShowDialog.h"
#include <QPixmap>
FImageShowDialog::FImageShowDialog(FImage &image, Settings &settings,
                                   QWidget *parent)
    : QDialog(parent), ui(new Ui::FImageShowDialog) {
  this->f_image = &image;
  this->settings = &settings;
  ui->setupUi(this);
  this->draw_area = new FImageDrawAreaWidget(image, settings, this);
  ui->splitter->insertWidget(0, draw_area);
  ui->name_lbl->setText(image.get_name().split("/").last());
}

FImageShowDialog::~FImageShowDialog() {
  delete ui;
  delete draw_area;
}

void FImageShowDialog::on_splitter_splitterMoved(int pos, int index) {}
