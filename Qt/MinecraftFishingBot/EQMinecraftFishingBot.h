#pragma once

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QThread>
#include "EQMinecraftFishingBotWorker.h"

class EQMinecraftFishingBot : public QMainWindow
{
	Q_OBJECT

public:
	EQMinecraftFishingBot(QWidget *parent = nullptr);
	~EQMinecraftFishingBot();

public slots:
	void displayCapture(const QPixmap capture);

private:
	QThread workerThread;
	EQMinecraftFishingBotWorker* worker;

	QLabel* userCapture;

	QGroupBox* initActivationLayout();
	QGroupBox* initParameters();
	QVBoxLayout* initHelpLayout();
};