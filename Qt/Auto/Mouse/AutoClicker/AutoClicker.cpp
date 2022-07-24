#include "AutoClicker.h"
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
	int previousClickHoldTime{};
	QIntValidator* intValidator{ new QIntValidator };
	intValidator->setRange(1, INT_MAX);
	MyLineEdit* clickHoldTimeEdit{ new MyLineEdit };
	clickHoldTimeEdit->setText(QString::number(50));
	clickHoldTimeEdit->setValidator(intValidator);
	connect(clickHoldTimeEdit, &MyLineEdit::focussed, [&previousClickHoldTime, &clickHoldTime, clickHoldTimeEdit, this](bool focussed) {
		if (focussed)
		{
			previousClickHoldTime = clickHoldTimeEdit->text().toInt();
			clickHoldTimeEdit->setReadOnly(false);
			// Fucking cursor stays even when out of focus?? So I had to set read only... check this
		}
		else
		{
			clickHoldTimeEdit->setReadOnly(true);

			clickHoldTime = clickHoldTimeEdit->text().toInt();
			//QMessageBox::critical(this, tr("Focussed?"), QString(focussed ? "Yes" : "No"), QMessageBox::Ok);
		}
	});
	clickHoldTimeLayout->addWidget(clickHoldTimeEdit);

	QHBoxLayout* timeBetweenClickLayout{ new QHBoxLayout };
	timeBetweenClickLayout->addWidget(new QLabel("Time between clicks (milliseconds):"));
	int timeBetweenClick{};
	QLineEdit* timeBetweenClickEdit{ new QLineEdit };
	timeBetweenClickEdit->setValidator(intValidator);
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


void MyLineEdit::focusInEvent(QFocusEvent* e)
{
	QLineEdit::focusInEvent(e);
	emit(focussed(true));
}

void MyLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusInEvent(e);
	emit(focussed(false));
}