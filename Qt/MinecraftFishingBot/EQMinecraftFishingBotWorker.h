#pragma once

#include <QObject>
#include <QString>
#include <QScreen>
#include <QPixmap>

class EQMinecraftFishingBotWorker  : public QObject
{
	Q_OBJECT

public:
	EQMinecraftFishingBotWorker();
	~EQMinecraftFishingBotWorker();

	static const short DEFAULT_PIXELS_OFFSET{ 30 };
	static const short MIN_PIXELS_OFFSET{ 20 };
	static const short MAX_PIXELS_OFFSET{ 100 };

public slots:
	void targetScreenChanged(QString& screenName);

signals:
	void captureTaken(QPixmap capture);

private:
	short pixelsOffset;
	unsigned int widthStartPixel;
	unsigned int heightStartPixel;
	QScreen* targetScreen();

	QPixmap takeScreenShot();

};
