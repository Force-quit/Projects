#pragma once

#include "EQSmartLineEdit.h"
#include "ui_EQUIRangedLineEdit.h"

class EQUIRangedLineEdit : public EQSmartLineEdit
{
	Q_OBJECT

public:
	EQUIRangedLineEdit(unsigned int bottom = 0, unsigned int top = 100, QWidget *parent = nullptr);
	~EQUIRangedLineEdit();

signals:
	void valueValidated(unsigned int value);

private:
	Ui::EQUIRangedLineEditClass ui;
	const unsigned int bottom;
	const unsigned int top;

private slots:
	void validate(const QString& text);
};