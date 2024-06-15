#include "EQIntLineEdit.h"
#include "EQIntValidator.h"

EQIntLineEdit::EQIntLineEdit(int iMinimum, int iMaximum)
	: mValidator{ new EQIntValidator(iMinimum, iMaximum) }
{
	setValidator(mValidator);
	connect(this, &QLineEdit::editingFinished, this, &EQIntLineEdit::verifyValue);
}

void EQIntLineEdit::verifyValue()
{
	QString currentText{ text() };
	if (currentText.isEmpty() || currentText.toInt() < mValidator->bottom())
	{
		int newValue{ mValidator->bottom() };
		setText(QString::number(newValue));
		emit valueChanged(newValue);
	}
}

void EQIntLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	verifyValue();
}