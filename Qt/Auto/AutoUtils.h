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

	static const std::unordered_map<int, QString> VIRTUAL_KEYS;
	static void playSound(const QUrl& audioFilePath);
	static const QString ROOT_CONFIG_PATH;
	static const QChar DEFAULT_ACTIVATION_KEY;

private:
	Ui::AutoUtilsClass ui;
	static QMediaPlayer* mediaPlayer;
	static QAudioOutput* audioOutput;
};