#include "EQUIRangedLineEdit.h"
#include "EQSmartLineEdit.h"
#include <QIntValidator>

EQUIRangedLineEdit::EQUIRangedLineEdit(unsigned int bottom, unsigned int top, QWidget* parent)
	: EQSmartLineEdit(parent), bottom(bottom), top(top)
{
	ui.setupUi(this);
	setValidator(new QIntValidator);
	connect(this, &EQSmartLineEdit::smartFocusOutEvent, this, &EQUIRangedLineEdit::validate);
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