#include "AutoUtils.h"
#include "./Mouse/Clicker/AutoClicker.h"
#include <QTabWidget>
#include <QIcon>
#include "../../Utilities/utils.h"

AutoUtils::AutoUtils(QWidget *parent)
	: QMainWindow(parent)
{
	emile::ensureFolderExists(CONFIG_PATH);
	ui.setupUi(this);

	QTabWidget* tab{ new QTabWidget };
	tab->addTab(new AutoClicker(CONFIG_PATH, tab), "Auto clicker");
	tab->addTab(new QWidget(), "Test");
	setCentralWidget(tab);
	resize(minimumSizeHint());

	setWindowTitle("Auto utilities");
	setWindowIcon(QIcon("program-icon-utilities.png"));
}

AutoUtils::~AutoUtils()
{}
