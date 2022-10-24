#include "AutoUtils.h"
#include "Mouse/Clicker/AutoClicker.h"
#include <QtWidgets/QApplication>
#include <filesystem>

void verifyFolderExists(const std::string& dirName)
{
    if (!std::filesystem::is_directory(dirName))
        std::filesystem::create_directory(dirName);
}

int main(int argc, char *argv[])
{
    verifyFolderExists(AutoClicker::CLICKER_CONFIG_PATH);
    QApplication a(argc, argv);
    AutoUtils w;
    w.show();
    return a.exec();
}
