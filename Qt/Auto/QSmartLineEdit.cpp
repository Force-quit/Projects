#include "QSmartLineEdit.h"
#include <QFocusEvent>
#include <QLineEdit>


#include <Windows.h>

QSmartLineEdit::QSmartLineEdit(QWidget* parent)
	: QLineEdit(parent)
{
	ui.setupUi(this);
}

QSmartLineEdit::~QSmartLineEdit()
{}

void QSmartLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	emit smartFocusOutEvent(text());
}