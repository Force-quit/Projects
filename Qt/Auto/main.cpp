#include "AutoUtils.h"
#include "Mouse/Clicker/AutoClicker.h"
#include <QtWidgets/QApplication>
#include "../../Utilities/utils.h"

int main(int argc, char *argv[])
{
    emile::ensureFolderExists(AutoClicker::CLICKER_CONFIG_PATH);
    QApplication a(argc, argv);
    AutoUtils w;
    w.show();
    return a.exec();
}
