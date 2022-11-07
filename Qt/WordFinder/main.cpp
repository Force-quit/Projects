#include "WordFinder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WordFinder w;
    w.show();
    return a.exec();
}
