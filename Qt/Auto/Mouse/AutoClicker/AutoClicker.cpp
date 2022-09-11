#include "AutoClicker.h"
#include <Windows.h>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>
#include <QLineEdit>
#include <QMessageBox>


AutoClicker::AutoClicker(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWidget* centralWidget{ new QWidget };
	QHBoxLayout* centralLayout{ new QHBoxLayout };

	QVBoxLayout* leftLayout{ new QVBoxLayout };
	leftLayout->setAlignment(Qt::AlignTop);

	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };

	QHBoxLayout* clickHoldTimeLayout{ new QHBoxLayout };
	clickHoldTimeLayout->addWidget(new QLabel("Click hold time (milliseconds):"));
	int clickHoldTime{};
	QIntValidator* intValidator{ new QIntValidator };
	intValidator->setRange(1, INT_MAX);
	auto* clickHoldTimeEdit{ new QLineEdit };
	clickHoldTimeEdit->setText(QString::number(50));
	clickHoldTimeEdit->setValidator(intValidator);
	connect(clickHoldTimeEdit, &QLineEdit::textEdited, [&clickHoldTime, clickHoldTimeEdit](const QString& text) {
		clickHoldTime = text.toInt();
		if (text.length() == 0 || text[0] == '0' || clickHoldTime == 0)
			clickHoldTimeEdit->setStyleSheet("QLineEdit { background: rgb(255, 0, 0); }");
		else
			clickHoldTimeEdit->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");
	});
	clickHoldTimeLayout->addWidget(clickHoldTimeEdit);

	QHBoxLayout* timeBetweenClickLayout{ new QHBoxLayout };
	timeBetweenClickLayout->addWidget(new QLabel("Clicks interval (milliseconds):"));
	int timeBetweenClick{};
	QLineEdit* timeBetweenClickEdit{ new QLineEdit };
	timeBetweenClickEdit->setText(QString::number(100));
	timeBetweenClickEdit->setValidator(intValidator);
	connect(timeBetweenClickEdit, &QLineEdit::textEdited, [&timeBetweenClick, timeBetweenClickEdit](const QString& text) {
		auto tempClickTime = text.toInt();
		if (text.length() == 0 || text[0] == '0' || tempClickTime > INT_MAX)
			timeBetweenClickEdit->setStyleSheet("QLineEdit { background: rgb(255, 0, 0); }");
		else
		{
			timeBetweenClickEdit->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");
			timeBetweenClick = tempClickTime;
		}
		});
	timeBetweenClickLayout->addWidget(timeBetweenClickEdit);

	parametersLayout->addLayout(clickHoldTimeLayout);
	parametersLayout->addLayout(timeBetweenClickLayout);
	parameters->setLayout(parametersLayout);
	leftLayout->addWidget(parameters);

	QGroupBox* saveAndLoadGroupBox{ new QGroupBox("Save or load parameters") };
	QHBoxLayout* saveAndLoadLayout{ new QHBoxLayout };
	QPushButton* saveButton{ new QPushButton("Save") };
	QPushButton* loadButton{ new QPushButton("Load") };
	saveAndLoadLayout->addWidget(saveButton);
	saveAndLoadLayout->addWidget(loadButton);
	saveAndLoadGroupBox->setLayout(saveAndLoadLayout);
	leftLayout->addWidget(saveAndLoadGroupBox);

	centralLayout->addLayout(leftLayout);
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
}