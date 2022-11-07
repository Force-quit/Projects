#include "AutoUtils.h"
#include "Mouse/Clicker/AutoClicker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoUtils w;
    w.show();
    return a.exec();
}
