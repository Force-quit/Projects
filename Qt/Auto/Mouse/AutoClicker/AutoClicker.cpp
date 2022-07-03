#include "AutoClicker.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSlider>
#include <QLabel>

AutoClicker::AutoClicker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWidget* centralWidget{ new QWidget };
	QHBoxLayout* centralLayout{ new QHBoxLayout };
	
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };
	QHBoxLayout* clickHoldTimeLayout{ new QHBoxLayout };
	QSlider* clickHoldTimeSlider{ new QSlider };
	clickHoldTimeSlider->setOrientation(Qt::Orientation::Horizontal);
	clickHoldTimeLayout->addWidget(new QLabel("Click hold time :"));
	clickHoldTimeLayout->addWidget(clickHoldTimeSlider);
	parametersLayout->addLayout(clickHoldTimeLayout);
	parameters->setLayout(parametersLayout);
	centralLayout->addWidget(parameters);

	QVBoxLayout* rightLayout{ new QVBoxLayout };
	centralLayout->addLayout(rightLayout);


	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
}