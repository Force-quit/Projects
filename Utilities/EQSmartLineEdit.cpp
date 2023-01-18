#include "EQSmartLineEdit.h"
#include <QLineEdit>
#include <QFocusEvent>

EQSmartLineEdit::EQSmartLineEdit(QWidget *parent) 
	: QLineEdit(parent)
{
	// TODO Temporary 
	connect(this, &QLineEdit::returnPressed, this, &QWidget::clearFocus);
}

void EQSmartLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	emit smartFocusOutEvent(text());
}

EQSmartLineEdit::~EQSmartLineEdit() {}