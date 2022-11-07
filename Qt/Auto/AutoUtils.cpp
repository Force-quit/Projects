#include "AutoUtils.h"
#include "./Mouse/Clicker/AutoClicker.h"
#include <QTabWidget>
#include <QIcon>

AutoUtils::AutoUtils(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QTabWidget* tab{ new QTabWidget };
	tab->addTab(new AutoClicker, "Auto clicker");
	tab->addTab(new QWidget(), "Test");
	setCentralWidget(tab);
	resize(minimumSizeHint());

	setWindowTitle("Auto utilities");
	setWindowIcon(QIcon("program-icon-utilities.png"));
}

AutoUtils::~AutoUtils()
{}
