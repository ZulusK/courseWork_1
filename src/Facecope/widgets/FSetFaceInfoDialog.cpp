#include "FSetFaceInfoDialog.h"
#include "ui_FSetFaceInfoDialog.h"
#include <FacecopeUtils.h>
#include <QPixmap>
#include <FImage.h>
FSetFaceInfoDialog::FSetFaceInfoDialog(Facecope &facecope, FFace &face, FImage &f_image,
                                       QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::FSetFaceInfoDialog)
{
    ui->setupUi(this);
    this->facecope=&facecope;
    this->face=&face;
    this->f_image=&f_image;
    auto q_image=Mat2QImage(f_image.get_face_cv_image(&face)).scaled(ui->face_L->size(),Qt::IgnoreAspectRatio);
    this->ui->face_L->setPixmap(QPixmap::fromImage(q_image));
    if(face.get_info().gender==MALE){
        ui->radioButton->setChecked(true);
    }else{
        ui->radioButton_2->setChecked(true);
    }
}

FSetFaceInfoDialog::~FSetFaceInfoDialog()
{
    delete ui;
}

void FSetFaceInfoDialog::on_buttonBox_accepted()
{
    if(ui->radioButton->isChecked()){
        //if male
        face->get_info().gender=MALE;
    }else{
        //if female
        face->get_info().gender=FEMALE;
    }
}
