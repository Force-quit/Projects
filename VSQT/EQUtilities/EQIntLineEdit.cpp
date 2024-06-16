#include "EQIntLineEdit.h"
#include "EQIntValidator.h"

EQIntLineEdit::EQIntLineEdit(int iMinimum, int iMaximum, int iDefaultValue)
	: mValidator{ new EQIntValidator(iMinimum, iMaximum) },
	mPreviousValue{ iDefaultValue }
{
	setValidator(mValidator);
	setText(QString::number(mPreviousValue));
	connect(this, &QLineEdit::editingFinished, this, &EQIntLineEdit::verifyValue);
}

void EQIntLineEdit::verifyValue()
{
	QString wText(text());

	if (wText.isEmpty() || wText.toInt() < mValidator->bottom())
	{
		setText(QString::number(mValidator->bottom()));
	}
	
	wText = text();
	int wCurrentValue{ wText.toInt() };
	if (wCurrentValue != mPreviousValue)
	{
		mPreviousValue = wCurrentValue;
		emit valueChanged(mPreviousValue);
	}
}

void EQIntLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	verifyValue();
}