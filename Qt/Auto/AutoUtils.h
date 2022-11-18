#pragma once

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <unordered_map>
#include <QUrl>
#include "ui_AutoUtils.h"
#include <QString>

class AutoUtils : public QMainWindow
{
	Q_OBJECT

public:
	AutoUtils(QWidget *parent = nullptr);
	~AutoUtils();

	static const QString ROOT_CONFIG_PATH;
	static const QChar DEFAULT_ACTIVATION_KEY;
	void playSound(const QUrl& audioFilePath);

private:
	Ui::AutoUtilsClass ui;
	QMediaPlayer* mediaPlayer;
	QAudioOutput* audioOutput;
};