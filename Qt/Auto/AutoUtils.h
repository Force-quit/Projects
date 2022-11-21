#pragma once

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <unordered_map>
#include <QUrl>
#include <QString>

class AutoUtils : public QMainWindow
{
	Q_OBJECT

public:
	AutoUtils(QWidget* parent = nullptr);
	~AutoUtils();

	const QString ROOT_CONFIG_PATH{ "Configs" };
	const char DEFAULT_ACTIVATION_KEY{ 'X' };
	const short DEFAULT_ACTIVATION_CODE{ 0x58 };
	void playSound(const QUrl& audioFilePath);

private:
	QMediaPlayer* mediaPlayer;
	QAudioOutput* audioOutput;
};