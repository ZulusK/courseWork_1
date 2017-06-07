#ifndef STARTMENUFORM_H
#define STARTMENUFORM_H

#include <QWidget>
#include <FMainWindow.h>
namespace Ui {
class StartMenuForm;
}

class StartMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenuForm(FMainWindow *parent);
    ~StartMenuForm();

private slots:
    void on_open_btn_clicked();

private:
    Ui::StartMenuForm *ui;
    FMainWindow  * parent;
};

#endif // STARTMENUFORM_H
