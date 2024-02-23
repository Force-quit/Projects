#pragma once
#include <QRegularExpressionValidator>

class EQTextValidator : public QRegularExpressionValidator
{
	Q_OBJECT

public:
	EQTextValidator(QObject* parent = nullptr);
	
	
	void fixup(QString& input) const override;
	QValidator::State validate(QString& input, int& pos) const override;
};

