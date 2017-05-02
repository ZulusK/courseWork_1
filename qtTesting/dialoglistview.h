#ifndef DIALOGLISTVIEW_H
#define DIALOGLISTVIEW_H

#include <QDialog>

namespace Ui {
class DialogListView;
}

class DialogListView : public QDialog
{
    Q_OBJECT

public:
    explicit DialogListView(QWidget *parent = 0);
    ~DialogListView();

private slots:
    void on_changeBtn_clicked();

    void on_removeBtn_clicked();

    void on_addBtn_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::DialogListView *ui;
};

#endif // DIALOGLISTVIEW_H
