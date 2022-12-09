#include "EQMinecraftFishingBotWorker.h"

EQMinecraftFishingBotWorker::EQMinecraftFishingBotWorker()

{
	/*widthStartPixel = (targetScreen->size().width() / 2) - pixelsOffset;
	heightStartPixel = (targetScreen->size().height() / 2) - pixelsOffset;*/

    //QTimer* timer{ new QTimer };
    //connect(timer, &QTimer::timeout, [this]() {
    //    imageLabel->setPixmap(takeScreenShot());
    //    });
    //timer->start(1);
}

EQMinecraftFishingBotWorker::~EQMinecraftFishingBotWorker()
{}

//QPixmap EQMinecraftFishingBotWorker::takeScreenShot()
//{
//    return targetScreen->grabWindow(0, widthStartPixel, heightStartPixel, pixelsOffset * 2, pixelsOffset * 2);
//}

    /*for (short i = 0; i < img.width(); ++i)
    {
        for (short j = 0; i < img.height(); ++j)
        {
            QColor pixelColor = img.pixelColor(i, j);
            auto a = pixelColor.black();
            qDebug(pixelColor.name().toStdString().c_str());
        }
    }*/

void EQMinecraftFishingBotWorker::targetScreenChanged(QString& screenName)
{

}