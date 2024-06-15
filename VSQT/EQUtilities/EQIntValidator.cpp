#include "EQIntValidator.h"

EQIntValidator::EQIntValidator(int iMinimum, int iMaximum)
	: QIntValidator(iMinimum, iMaximum)
{

}

QValidator::State EQIntValidator::validate(QString& input, int& pos) const
{
	if (QIntValidator::validate(input, pos) == QValidator::State::Invalid)
	{
		bool inputIsNumber{};
		input.toInt(&inputIsNumber);
		if (!inputIsNumber)
		{
			return QValidator::State::Invalid;
		}
	}
	
	if (input.toInt() > top())
	{
		input = QString::number(top());
	}

	// If input < bottom() or input is empty, 
	// EQIntLineEdit::verifyValue will catch it
	return QValidator::State::Acceptable;
}