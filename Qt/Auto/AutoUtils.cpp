#include <QString>
#include "AutoUtils.h"
#include <QChar>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QWidget>
#include <QMainWindow>
#include <QDir>
#include <QTabWidget>
#include "Mouse/Clicker/AutoClicker.h"
#include <QIcon>
#include <QUrl>

const QString AutoUtils::ROOT_CONFIG_PATH = "Configs";
const QChar AutoUtils::DEFAULT_ACTIVATION_KEY{ 'X' };
QMediaPlayer* AutoUtils::mediaPlayer{};
QAudioOutput* AutoUtils::audioOutput{};

AutoUtils::AutoUtils(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QDir().mkdir(ROOT_CONFIG_PATH);

	QTabWidget* tab{ new QTabWidget };
	tab->setMovable(true);
	tab->addTab(new AutoClicker(tab), "Auto clicker");
	tab->addTab(new QWidget(tab), "Test");
	tab->addTab(new QWidget(tab), "Test");
	tab->addTab(new QWidget(tab), "Test");
	tab->addTab(new QWidget(tab), "Test");
	setCentralWidget(tab);

	resize(minimumSizeHint());	
	setWindowTitle("Auto utilities");
	setWindowIcon(QIcon("program-icon-utilities.png"));
	AutoUtils::playSound(QUrl("autoclicker-on.wav"));
}

void AutoUtils::playSound(const QUrl& audioFilePath)
{
	if (AutoUtils::mediaPlayer == nullptr)
	{
		AutoUtils::mediaPlayer = new QMediaPlayer;
		AutoUtils::audioOutput = new QAudioOutput;
		AutoUtils::mediaPlayer->setAudioOutput(audioOutput);
	}

	AutoUtils::mediaPlayer->setSource(audioFilePath);
	AutoUtils::mediaPlayer->play();
}

AutoUtils::~AutoUtils()
{
	delete AutoUtils::mediaPlayer;
	delete AutoUtils::audioOutput;
	AutoUtils::mediaPlayer = nullptr;
	AutoUtils::audioOutput = nullptr;
}