#include "EQUIRangedLineEdit.h"
#include "EQSmartLineEdit.h"
#include <QIntValidator>

EQUIRangedLineEdit::EQUIRangedLineEdit(unsigned int bottom, unsigned int top, QWidget* parent)
	: EQSmartLineEdit(parent), validator()
{
	ui.setupUi(this);
	validator = new QIntValidator(bottom, top);
	setValidator(validator);
	connect(this, &EQSmartLineEdit::smartFocusOutEvent, this, &EQUIRangedLineEdit::validate);
}

void EQUIRangedLineEdit::validate(const QString& text)
{
	auto temp{ text.toULongLong() };
	if (temp > UINT_MAX)
	{
		timeBetweenClicks = UINT_MAX;
		timeBetweenClicksEdit->setText(QString::number(timeBetweenClicks));
	}
	else if (temp <= 0)
	{
		timeBetweenClicks = 1;
		timeBetweenClicksEdit->setText(QString::number(timeBetweenClicks));
	}
	else
		timeBetweenClicks = temp;
}

EQUIRangedLineEdit::~EQUIRangedLineEdit()
{
	delete validator;
}