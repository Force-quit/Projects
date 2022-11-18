#include <QApplication>
#include "WordFinder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WordFinder w;
    w.show();
    return a.exec();
}