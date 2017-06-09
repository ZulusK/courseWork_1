#include "FSetFaceInfoDialog.h"
#include "ui_FSetFaceInfoDialog.h"

FSetFaceInfoDialog::FSetFaceInfoDialog(Facecope *facecope, FFace *face, FImage *f_image,
                                       QWidget *parent ) :
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
