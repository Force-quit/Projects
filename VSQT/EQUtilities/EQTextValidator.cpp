#include "EQTextValidator.h"

EQTextValidator::EQTextValidator()
{
	setRegularExpression(QRegularExpression("\\p{L}*"));
}

void EQTextValidator::fixup(QString& input) const
{
	input = input.simplified();
}

QValidator::State EQTextValidator::validate(QString& input, int& pos) const
{
	fixup(input);
	return QRegularExpressionValidator::validate(input, pos);
}
