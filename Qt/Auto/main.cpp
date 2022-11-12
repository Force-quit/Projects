#include "AutoUtils.h"
#include <QtWidgets/QApplication>
#include <Windows.h>

int main(int argc, char *argv[])
{
    Beep(160, 2000);
    QApplication a(argc, argv);
    AutoUtils w;
    w.show();
    return a.exec();
}