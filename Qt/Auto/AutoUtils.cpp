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

AutoUtils::AutoUtils(QWidget* parent)
	: QMainWindow(parent), mediaPlayer(), audioOutput()
{
	QDir().mkdir(ROOT_CONFIG_PATH);

	QTabWidget* tab{ new QTabWidget };
	tab->setMovable(true);
	tab->addTab(new AutoClicker(tab), "Auto clicker");
	tab->addTab(new QWidget(tab), "Input recorder");
	setCentralWidget(tab);

	resize(minimumSizeHint());	
	setWindowTitle("Auto utilities");
	setWindowIcon(QIcon("program-icon-utilities.png"));

	mediaPlayer = new QMediaPlayer;
	audioOutput = new QAudioOutput;
	mediaPlayer->setAudioOutput(audioOutput);
	playSound(QUrl("autoclicker-on.wav"));
}

void AutoUtils::playSound(const QUrl& audioFilePath)
{
	mediaPlayer->setSource(audioFilePath);
	mediaPlayer->play();
}

AutoUtils::~AutoUtils()
{
	delete mediaPlayer;
	delete audioOutput;
}