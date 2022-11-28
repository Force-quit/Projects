#include <QString>
#include "AutoUtils.h"
#include <QChar>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QWidget>
#include <QMainWindow>
#include <QDir>
#include "../../Utilities/EQTabWidget.h"
#include "Mouse/Clicker/AutoClicker.h"
#include <QIcon>
#include <QUrl>

const QString AutoUtils::ROOT_CONFIG_PATH{ "Configs" };
const QChar AutoUtils::DEFAULT_ACTIVATION_KEY{ 'X' };

AutoUtils::AutoUtils(QWidget* parent)
	: QMainWindow(parent), mediaPlayer(), audioOutput()
{
	QDir().mkdir(ROOT_CONFIG_PATH);

	EQTabWidget* tab{ new EQTabWidget };
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