#include "EQMinecraftFishingBot.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include <QGuiApplication>
#include <QScreen>
#include <QString>
#include <QImage>
#include "EQMinecraftFishingBotWorker.h"
#include <QCheckBox>

EQMinecraftFishingBot::EQMinecraftFishingBot(QWidget *parent)
	: QMainWindow(parent)
{
    QWidget* centralWidget{ new QWidget };
    QHBoxLayout* centralLayout{ new QHBoxLayout };
   
    QGroupBox* parameters{ initParameters() };
    QVBoxLayout* helperLayout{ initHelpLayout() };

    centralLayout->addWidget(parameters);
    centralLayout->addLayout(helperLayout);

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
}

QGroupBox* EQMinecraftFishingBot::initParameters()
{
    QGroupBox* parameters{ new QGroupBox("Parameters") };

    QVBoxLayout* parametersLayout{ new QVBoxLayout };
    parametersLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* targetScreenLayout{ new QHBoxLayout };
    QLabel* targetScreenLabel{ new QLabel("Target screen :") };
    QComboBox* targetScreenComboBox{ new QComboBox };
    for (QScreen* screen : QGuiApplication::screens())
        targetScreenComboBox->addItem(screen->name());
    targetScreenLayout->addWidget(targetScreenLabel);
    targetScreenLayout->addWidget(targetScreenComboBox);

    QHBoxLayout* captureSizeLayout{ new QHBoxLayout };
    QLabel* captureSizeLabel{ new QLabel("Capture size :") };
    unsigned int min{ EQMinecraftFishingBotWorker::MIN_PIXELS_OFFSET };
    unsigned int max{ EQMinecraftFishingBotWorker::MAX_PIXELS_OFFSET };
    EQUIRangedLineEdit* captureSizeLineEdit{ new EQUIRangedLineEdit(min, max) };
    captureSizeLineEdit->setText(QString::number(EQMinecraftFishingBotWorker::DEFAULT_PIXELS_OFFSET));
    captureSizeLayout->addWidget(captureSizeLabel);
    captureSizeLayout->addWidget(captureSizeLineEdit);

    parametersLayout->addLayout(targetScreenLayout);
    parametersLayout->addLayout(captureSizeLayout);

    parameters->setLayout(parametersLayout);
    return parameters;
}

QVBoxLayout* EQMinecraftFishingBot::initHelpLayout()
{
    QVBoxLayout* helpLayout{ new QVBoxLayout };
    helpLayout->setAlignment(Qt::AlignCenter);

    QLabel* helpLabel{ new QLabel("Match your capture to look like this")};
    helpLabel->setAlignment(Qt::AlignHCenter);
    QLabel* helpExample{ new QLabel };
    helpExample->setPixmap(QPixmap::fromImage(QImage("captureExample.png")));
    helpExample->setAlignment(Qt::AlignHCenter);
   
    QLabel* helpLabel2{ new QLabel("Your capture") };
    helpLabel2->setAlignment(Qt::AlignHCenter);
    QLabel* helpYourCapture{ new QLabel };
    helpYourCapture->setPixmap(QPixmap::fromImage(QImage("captureExample.png")));
    helpYourCapture->setAlignment(Qt::AlignHCenter);
    QHBoxLayout* displayYourCaptureLayout{ new QHBoxLayout };
    displayYourCaptureLayout->setAlignment(Qt::AlignCenter);
    QCheckBox* displayYourCapture{ new QCheckBox("Show your capture") };
    displayYourCaptureLayout->addWidget(displayYourCapture);


    helpLayout->addWidget(helpLabel);
    helpLayout->addWidget(helpExample);
    helpLayout->addWidget(helpLabel2);
    helpLayout->addWidget(helpYourCapture);
    helpLayout->addLayout(displayYourCaptureLayout);
    return helpLayout;
}

EQMinecraftFishingBot::~EQMinecraftFishingBot() {}