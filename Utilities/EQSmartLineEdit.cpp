#include "EQSmartLineEdit.h"
#include <QLineEdit>
#include <QFocusEvent>

EQSmartLineEdit::EQSmartLineEdit(QWidget *parent) 
	: QLineEdit(parent)
{
	// TODO Temporary 
	connect(this, &QLineEdit::returnPressed, this, &QWidget::clearFocus);
}

EQSmartLineEdit::~EQSmartLineEdit() {}

void EQSmartLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	emit smartFocusOutEvent(text());
}