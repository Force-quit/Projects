#include <QApplication>
#include "EQMinecraftFishingBot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EQMinecraftFishingBot w;
    w.show();
    return a.exec();
}