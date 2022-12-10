#pragma once

#include "EQSmartLineEdit.h"
#include <QString>

class EQUIRangedLineEdit : public EQSmartLineEdit
{
	Q_OBJECT

public:
	EQUIRangedLineEdit(unsigned int bottom = 0, unsigned int top = 100, unsigned int defaultValue = 50, QWidget *parent = nullptr);
	~EQUIRangedLineEdit();

signals:
	void valueValidated(unsigned int value);

private:
	const unsigned int bottom;
	const unsigned int top;

private slots:
	void validate(const QString& text);
};