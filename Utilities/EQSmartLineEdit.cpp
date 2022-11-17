#include "EQSmartLineEdit.h"

EQSmartLineEdit::EQSmartLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	ui.setupUi(this);
}

EQSmartLineEdit::~EQSmartLineEdit()
{}


void EQSmartLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	emit smartFocusOutEvent(text());
}