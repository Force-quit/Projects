#pragma once

#include <QLineEdit>
#include "ui_EQSmartLineEdit.h"
#include <QFocusEvent>

class EQSmartLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	EQSmartLineEdit(QWidget *parent = nullptr);
	~EQSmartLineEdit();

signals:
	void smartFocusOutEvent(const QString& text);

protected:
	void focusOutEvent(QFocusEvent* e) override;

private:
	Ui::EQSmartLineEditClass ui;
};
