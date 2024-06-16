#pragma once

#include <QLineEdit>
#include "EQIntValidator.h"

class EQIntLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	EQIntLineEdit(int iMinimum, int iMaximum, int iDefaultValue);

signals:
	void valueChanged(int iNewValue);

protected:
	void focusOutEvent(QFocusEvent* iFocusEvent) override;

private slots:
	void verifyValue();

private:
	EQIntValidator* mValidator;
	int mPreviousValue;
};
