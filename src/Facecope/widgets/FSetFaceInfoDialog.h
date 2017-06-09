#ifndef FSETFACEINFODIALOG_H
#define FSETFACEINFODIALOG_H

#include <QDialog>

namespace Ui {
class FSetFaceInfoDialog;
}

class FSetFaceInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FSetFaceInfoDialog(QWidget *parent = 0);
    ~FSetFaceInfoDialog();

private:
    Ui::FSetFaceInfoDialog *ui;
};

#endif // FSETFACEINFODIALOG_H
