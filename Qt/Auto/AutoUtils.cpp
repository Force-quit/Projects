#include "AutoUtils.h"
#include "./Mouse/Clicker/AutoClicker.h"
#include <QTabWidget>
#include <QIcon>
#include <QDir>

AutoUtils::AutoUtils(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QDir().mkdir(QString::fromStdString(CONFIG_PATH));

	QTabWidget* tab{ new QTabWidget };
	tab->setMovable(true);
	tab->addTab(new AutoClicker(tab, CONFIG_PATH, VIRTUAL_KEYS), "Auto clicker");
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