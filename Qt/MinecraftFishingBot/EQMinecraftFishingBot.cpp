#include "EQMinecraftFishingBot.h"
#include <QScreen>
#include <QWindow>
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QLabel>
#include <QBoxLayout>
#include <QTimer>

EQMinecraftFishingBot::EQMinecraftFishingBot(QWidget *parent)
	: QMainWindow(parent), targetScreen(QGuiApplication::primaryScreen()),  widthStartPixel(), heightStartPixel(), imageLabel()
{
    QWidget* centralWidget{ new QWidget };
    QHBoxLayout* centralLayout{ new QHBoxLayout };
    centralLayout->setAlignment(Qt::AlignCenter);

    widthStartPixel = (targetScreen->size().width() / 2) - screenshotPixelsOffset;
    heightStartPixel = (targetScreen->size().height() / 2) - screenshotPixelsOffset;
    imageLabel =  new QLabel;
    centralLayout->addWidget(imageLabel);


    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    QTimer* timer{ new QTimer };
    connect(timer, &QTimer::timeout, [this]() {
        imageLabel->setPixmap(takeScreenShot());
    });
    timer->start(1);
}


QPixmap EQMinecraftFishingBot::takeScreenShot()
{
    return targetScreen->grabWindow(0, widthStartPixel, heightStartPixel, screenshotPixelsOffset * 2, screenshotPixelsOffset * 2);
}

QGroupBox* EQMinecraftFishingBot::initParameters()
{
    return nullptr;
}

QVBoxLayout* EQMinecraftFishingBot::initHelpLayout()
{
    return nullptr;
}

EQMinecraftFishingBot::~EQMinecraftFishingBot() {}
    /*for (short i = 0; i < img.width(); ++i)
    {
        for (short j = 0; i < img.height(); ++j)
        {
            QColor pixelColor = img.pixelColor(i, j);
            auto a = pixelColor.black();
            qDebug(pixelColor.name().toStdString().c_str());
        }
    }*/