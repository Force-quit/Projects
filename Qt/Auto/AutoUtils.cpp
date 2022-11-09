#include "AutoUtils.h"
#include "./Mouse/Clicker/AutoClicker.h"
#include <QTabWidget>
#include <QIcon>
#include <QDir>

AutoUtils::AutoUtils(QWidget* parent)
	: QMainWindow(parent)
{
	QDir().mkdir(QString::fromStdString(CONFIG_PATH));
	ui.setupUi(this);

	QTabWidget* tab{ new QTabWidget };
	tab->setMovable(true);
	tab->addTab(new AutoClicker(CONFIG_PATH, tab), "Auto clicker");
	tab->addTab(new QWidget(tab), "Test");
	tab->addTab(new QWidget(tab), "Test");
	tab->addTab(new QWidget(tab), "Test");
	tab->addTab(new QWidget(tab), "Test");
	setCentralWidget(tab);

	resize(minimumSizeHint());	
	setWindowTitle("Auto utilities");
	setWindowIcon(QIcon("program-icon-utilities.png"));
}

AutoUtils::~AutoUtils(){}