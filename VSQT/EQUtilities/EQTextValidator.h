#pragma once
#include <QRegularExpressionValidator>

class EQTextValidator : public QRegularExpressionValidator
{
	Q_OBJECT

public:
	EQTextValidator();
	void fixup(QString& input) const override;
	QValidator::State validate(QString& input, int& pos) const override;
};

