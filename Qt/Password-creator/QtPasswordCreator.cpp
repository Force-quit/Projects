#include "QtPasswordCreator.h"
#include "../../Utilities/utils.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <Windows.h>
#include <QPlainTextEdit>

QtPasswordCreator::QtPasswordCreator(QWidget* parent)
	: QWidget(parent)
{
	QHBoxLayout* centalLayout{ new QHBoxLayout };

	QVBoxLayout* sliderLayout{ new QVBoxLayout };
	QSlider* passwordLengthSlider{ new QSlider };
	passwordLengthSlider->setMinimum(1);
	passwordLengthSlider->setValue(20);
	passwordLengthSlider->setMaximum(200);

	
	QLabel* passwordLengthText{ new QLabel(QString::number(passwordLengthSlider->value()))};
	passwordLengthText->setAlignment(Qt::AlignCenter);

	connect(passwordLengthSlider, &QSlider::valueChanged, [passwordLengthText](int value) {
		passwordLengthText->setText(QString("%1").arg(value));
		});

	QVBoxLayout* sliderAlignLayout{ new QVBoxLayout };
	sliderAlignLayout->setAlignment(Qt::AlignHCenter);
	sliderAlignLayout->addSpacing(20);
	sliderAlignLayout->addWidget(passwordLengthSlider);
	sliderAlignLayout->addSpacing(20);

	sliderLayout->addWidget(new QLabel("Password length"));
	sliderLayout->addWidget(passwordLengthText);
	sliderLayout->addLayout(sliderAlignLayout);

	QVBoxLayout* passwordLayout{ new QVBoxLayout };
	QPlainTextEdit* passwordText{ new QPlainTextEdit };
	QPushButton* generatePasswordButton{ new QPushButton("Generate password") };
	connect(generatePasswordButton, &QPushButton::clicked, [passwordText, passwordLengthSlider]() {
		passwordText->setPlainText(QString::fromUtf8(emile::PasswordGenerator::generate(emile::PasswordGenerator::DEFAULT_ALPHABET, passwordLengthSlider->value())));
		});
	QPushButton* copyPasswordButton{ new QPushButton("Copy password") };

	connect(copyPasswordButton, &QPushButton::clicked, [passwordText]() {
		emile::copyToClipBoard(passwordText->toPlainText().toStdString());
		MessageBoxA(0, "Password copied to clipboard!", "Password generator", MB_OK);
		});

	passwordLayout->addWidget(passwordText);
	passwordLayout->addWidget(generatePasswordButton);
	passwordLayout->addWidget(copyPasswordButton);

	centalLayout->addLayout(sliderLayout);
	centalLayout->addLayout(passwordLayout);
	setLayout(centalLayout);
}