#include "EQSmartLineEdit.h"
#include <QLineEdit>
#include <QFocusEvent>

EQSmartLineEdit::EQSmartLineEdit(QWidget *parent) : QLineEdit(parent) {}

EQSmartLineEdit::~EQSmartLineEdit() {}

void EQSmartLineEdit::focusOutEvent(QFocusEvent* e)
{
	QLineEdit::focusOutEvent(e);
	emit smartFocusOutEvent(text());
}