#include "EQMinecraftFishingBotWorker.h"
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>
#include <QSize>
#include <QTimer>

EQMinecraftFishingBotWorker::EQMinecraftFishingBotWorker()
	: captureSize(DEFAULT_CAPTURE_SIZE), heightStartPixel(), widthStartPixel(), captureInterval(DEFAULT_INTERVAL),
	active(), captureHelp(), userActivation(), targetScreen()
{
	targetScreenChanged(QGuiApplication::primaryScreen()->name());
}

void EQMinecraftFishingBotWorker::captureSizeChanged(const unsigned short captureSize)
{
	//TODO fix this
	int diff{ abs(this->captureSize - captureSize) };

	if (this->captureSize < captureSize)
	{
		heightStartPixel -= diff;
		widthStartPixel -= diff;
	}
	else
	{
		heightStartPixel += diff;
		widthStartPixel += diff;
	}
	
	this->captureSize = captureSize;
}

void EQMinecraftFishingBotWorker::targetScreenChanged(const QString& screenName)
{
	for (QScreen* screen : QGuiApplication::screens())
	{
		if (screenName == screen->name())
		{
			targetScreen = screen;
			QSize targetScreenSize{ targetScreen->size() };
			widthStartPixel = targetScreenSize.width() / 2 - captureSize / 2;
			heightStartPixel = targetScreenSize.height() / 2 - captureSize / 2;
			break;
		}
	}
}

void EQMinecraftFishingBotWorker::rightClick()
{

}

void EQMinecraftFishingBotWorker::captureScreen()
{
	QPixmap capture = targetScreen->grabWindow(0, widthStartPixel, heightStartPixel, captureSize, captureSize);
	auto a = capture.size();
	if (captureHelp)
		emit captureTaken(capture);

	if (userActivation)
	{
		QImage captureImage = capture.toImage();
		bool hasBlack{};
		for (short i = 0; i < captureSize && !hasBlack; ++i)
		{
			for (short j = 0; j < captureSize && !hasBlack; ++j)
			{
				QColor pixelColor = captureImage.pixel(i, j);
				hasBlack = pixelColor.black() == 255;
			}
		}

		if (!hasBlack)
			qDebug("RightClicking");
		else
			qDebug("no");
	}
	
	if (userActivation || captureHelp)
		QTimer::singleShot(captureInterval, this, &EQMinecraftFishingBotWorker::captureScreen);
	else
		active = false;
}

void EQMinecraftFishingBotWorker::requestHelp()
{
	captureHelp = !captureHelp;
	if (captureHelp && !active)
	{
		active = true;
		QTimer::singleShot(captureInterval, this, &EQMinecraftFishingBotWorker::captureScreen);
	}
}

void EQMinecraftFishingBotWorker::activate()
{
	userActivation = !userActivation;
	if (userActivation && !active)
	{
		active = true;
		QTimer::singleShot(captureInterval, this, &EQMinecraftFishingBotWorker::captureScreen);
	}

}

void EQMinecraftFishingBotWorker::setCaptureInterval(const unsigned short interval)
{
	this->captureInterval = interval;
}
void EQMinecraftFishingBotWorker::stop()
{
	active = false;
	captureHelp = false;
}

EQMinecraftFishingBotWorker::~EQMinecraftFishingBotWorker() {}