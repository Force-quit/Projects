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

	static const unsigned short DEFAULT_CAPTURE_SIZE{ 30 };
	static const unsigned short MIN_CAPTURE_SIZE{ 20 };
	static const unsigned short MAX_CAPTURE_SIZE{ 100 };

	static const unsigned short DEFAULT_INTERVAL{ 50 };
	static const unsigned short MIN_INTERVAL{ 1 };
	static const unsigned short MAX_INTERVAL{ 1000 };

	void stop();

public slots:
	void setCaptureInterval(const unsigned short interval);
	void requestHelp();
	void activate();
	void captureSizeChanged(const unsigned short captureSize);
	void targetScreenChanged(const QString& screenName);

signals:
	void captureTaken(const QPixmap& capture);

private slots:
	void captureScreen();
	void rightClick();

private:
	QScreen* targetScreen;

	bool active;
	bool userActivation;
	bool captureHelp;

	unsigned short captureSize;
	unsigned short widthStartPixel;
	unsigned short heightStartPixel;
	unsigned short captureInterval;
};
