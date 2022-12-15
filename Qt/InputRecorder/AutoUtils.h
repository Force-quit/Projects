#pragma once

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <unordered_map>
#include <QUrl>
#include <QString>
#include <QChar>

class AutoUtils : public QMainWindow
{
	Q_OBJECT

public:
	AutoUtils(QWidget* parent = nullptr);
	~AutoUtils();

	static const QString ROOT_CONFIG_PATH;
	static const QChar DEFAULT_ACTIVATION_KEY;
	static const short DEFAULT_ACTIVATION_CODE{ 0x58 };

	void playSound(const QUrl& audioFilePath);

private:
	QMediaPlayer* mediaPlayer;
	QAudioOutput* audioOutput;
};