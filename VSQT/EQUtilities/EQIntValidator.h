#pragma once

#include <QIntValidator>
#include <QString>

class EQIntValidator : public QIntValidator
{
	Q_OBJECT

public:
	EQIntValidator(int iMinimum, int iMaximum);
	QValidator::State validate(QString& input, int& pos) const override;
};
