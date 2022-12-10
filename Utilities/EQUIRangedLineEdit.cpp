#include "EQUIRangedLineEdit.h"
#include "EQSmartLineEdit.h"
#include <QIntValidator>
#include <QString>

EQUIRangedLineEdit::EQUIRangedLineEdit(unsigned int bottom, unsigned int top, unsigned int defaultValue, QWidget* parent)
	: EQSmartLineEdit(parent), bottom(bottom), top(top)
{
	setValidator(new QIntValidator);
	connect(this, &EQSmartLineEdit::smartFocusOutEvent, this, &EQUIRangedLineEdit::validate);
	setText(QString::number(defaultValue));
}

void EQUIRangedLineEdit::validate(const QString& text)
{
	auto temp{ text.toULongLong() };
	unsigned int resultingValue{};
	if (temp > top)
		resultingValue = top;
	else if (temp < bottom)
		resultingValue = bottom;
	else
		resultingValue = temp;

	setText(QString::number(resultingValue));
	emit valueValidated(resultingValue);
}

EQUIRangedLineEdit::~EQUIRangedLineEdit() {}