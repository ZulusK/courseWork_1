#include "FileBrowserWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileBrowserWindow w;
    w.show();

    return a.exec();
}
