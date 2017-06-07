#include "StartMenuForm.h"
#include "ui_StartMenuForm.h"

StartMenuForm::StartMenuForm(FMainWindow *parent)
    : QWidget(parent), ui(new Ui::StartMenuForm) {
  ui->setupUi(this);
  this->parent = parent;
}

StartMenuForm::~StartMenuForm() { delete ui; }

void StartMenuForm::on_open_btn_clicked() {
  emit parent->signal_setCentralWidget(this, IMAGE_EDIT);
}
