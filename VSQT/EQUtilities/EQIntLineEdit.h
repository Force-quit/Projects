#pragma once

#include <QLineEdit>
#include "EQIntValidator.h"

class EQIntLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	EQIntLineEdit(int iMinimum, int iMaximum);

signals:
	void valueChanged(int iNewValue);

protected:
	void focusOutEvent(QFocusEvent* iFocusEvent) override;

private slots:
	void verifyValue();

private:
	EQIntValidator* mValidator;
};
