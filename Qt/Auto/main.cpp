#include <QApplication>
#include "AutoUtils.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
    Beep(200, 500);
    QApplication a(argc, argv);
    AutoUtils w;
    w.show();
    return a.exec();
}