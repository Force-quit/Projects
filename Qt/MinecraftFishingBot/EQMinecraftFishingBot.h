#pragma once

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QThread>


class EQMinecraftFishingBot : public QMainWindow
{
	Q_OBJECT

public:
	EQMinecraftFishingBot(QWidget *parent = nullptr);
	~EQMinecraftFishingBot();

private:

	QGroupBox* initParameters();
	QVBoxLayout* initHelpLayout();
};
