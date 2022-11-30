#include "QtWidgetsClass.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>

QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QMainWindow(parent), money()
{
	QVBoxLayout* centralLayout{ new QVBoxLayout };
	QHBoxLayout* buttonsLayout = initButtonsLayout();
	QHBoxLayout* labelsLayout = initLabelsLayout();
	centralLayout->addLayout(labelsLayout);
	centralLayout->addLayout(buttonsLayout);

	QWidget* centralWidget{ new QWidget };
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
	setWindowTitle("My game");
	resize(minimumSizeHint());
}

QHBoxLayout* QtWidgetsClass::initLabelsLayout()
{
	QHBoxLayout* labelsLayout{ new QHBoxLayout };
	labelsLayout->setAlignment(Qt::AlignLeft);
	QLabel* moneyText{ new QLabel("Money :") };
	moneyLabel = new QLabel(QString::number(money));
	labelsLayout->addWidget(moneyText);
	labelsLayout->addWidget(moneyLabel);
	return labelsLayout;
}

QHBoxLayout* QtWidgetsClass::initButtonsLayout()
{
	QHBoxLayout* buttonsLayout{ new QHBoxLayout };
	QPushButton* refreshButton{ new QPushButton("Refresh") };
	QPushButton* addButton{ new QPushButton("+ " + QString::number(MONEY_INCREMENT)) };
	QPushButton* resetButton{ new QPushButton("Reset") };
	buttonsLayout->addWidget(refreshButton);
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(resetButton);

	connect(refreshButton, &QPushButton::clicked, this, &QtWidgetsClass::refreshLabel);
	
	connect(addButton, &QPushButton::clicked, [this]() {
		money += MONEY_INCREMENT;
		refreshLabel();
	});

	connect(resetButton, &QPushButton::clicked, [this]() {
		money = 0;
		refreshLabel();
	});

	return buttonsLayout;
}

void QtWidgetsClass::refreshLabel()
{
	moneyLabel->setText(QString::number(money));
}

QtWidgetsClass::~QtWidgetsClass(){}