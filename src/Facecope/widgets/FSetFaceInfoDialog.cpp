#include "FSetFaceInfoDialog.h"
#include "ui_FSetFaceInfoDialog.h"

FSetFaceInfoDialog::FSetFaceInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FSetFaceInfoDialog)
{
    ui->setupUi(this);
}

FSetFaceInfoDialog::~FSetFaceInfoDialog()
{
    delete ui;
}

void FSetFaceInfoDialog::on_buttonBox_accepted()
{

}
