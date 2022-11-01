#include "AutoUtils.h"
#include "./Mouse/Clicker/AutoClicker.h"

AutoUtils::AutoUtils(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setCentralWidget(new AutoClicker);
	resize(minimumSizeHint());
}

AutoUtils::~AutoUtils()
{}
