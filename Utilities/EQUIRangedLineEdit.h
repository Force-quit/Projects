#pragma once

#include "EQSmartLineEdit.h"
#include "ui_EQUIRangedLineEdit.h"
#include <QIntValidator>

class EQUIRangedLineEdit : public EQSmartLineEdit
{
	Q_OBJECT

public:
	EQUIRangedLineEdit(unsigned int bottom = 0, unsigned int top = 100, QWidget *parent = nullptr);
	~EQUIRangedLineEdit();

signals:
	unsigned int finalValue();

private:
	Ui::EQUIRangedLineEditClass ui;
	unsigned int bottom;
	unsigned int top;

	QIntValidator* validator;

private slots:
	void validate(const QString& text);
};