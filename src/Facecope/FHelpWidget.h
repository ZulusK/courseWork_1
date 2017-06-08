#ifndef FHELPWIDGET_H
#define FHELPWIDGET_H

#include <QWidget>

namespace Ui {
class FHelpWidget;
}

class FHelpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FHelpWidget(QWidget *parent = 0);
    ~FHelpWidget();

private:
    Ui::FHelpWidget *ui;
};

#endif // FHELPWIDGET_H
