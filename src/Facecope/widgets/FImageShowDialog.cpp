#include "FImageShowDialog.h"
#include "ui_FImageShowDialog.h"
#include <QPixmap>
#include <opencv/cv.hpp>

FImageShowDialog::FImageShowDialog(Facecope &facecope, FImage &image,
                                   QWidget *parent)
    : QDialog(parent), ui(new Ui::FImageShowDialog) {
  this->f_image = &image;
  this->facecope = &facecope;
  ui->setupUi(this);
  this->draw_area = new FImageDrawAreaWidget( facecope, image,this);
  ui->splitter->insertWidget(0, draw_area);
  ui->name_lbl->setText(image.get_name().split("/").last());
  this->model = new FFaceModel(facecope, image, this);
  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

FImageShowDialog::~FImageShowDialog() {
  delete ui;
  delete draw_area;
  delete model;
}

void FImageShowDialog::on_splitter_splitterMoved(int pos, int index) {
  on_size_slider_sliderMoved(ui->size_slider->value());
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void FImageShowDialog::on_size_slider_sliderMoved(int position) {
  auto w = ui->tableView->rect().width() * position / 100.0;
  this->model->set_image_size(QSize(w, w));
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
}
