#pragma once

#include <QMainWindow>
#include "ui_EQMinecraftFishingBot.h"
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>

class EQMinecraftFishingBot : public QMainWindow
{
	Q_OBJECT

public:
	EQMinecraftFishingBot(QWidget *parent = nullptr);
	~EQMinecraftFishingBot();

private:
	const short screenshotPixelsOffset{ 80 };
	unsigned int widthStartPixel;
	unsigned int heightStartPixel;

	QScreen* targetScreen;
	QLabel* imageLabel;

	QGroupBox* initParameters();
	QVBoxLayout* initHelpLayout();

	QPixmap takeScreenShot();
};
