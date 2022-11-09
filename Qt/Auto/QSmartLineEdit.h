#pragma once

#include <QLineEdit>
#include <QFocusEvent>
#include "ui_QSmartLineEdit.h"

class QSmartLineEdit : public QLineEdit
{
	Q_OBJECT

		Ui::QSmartLineEditClass ui;

public:
	QSmartLineEdit(QWidget* parent = nullptr);
	~QSmartLineEdit();

signals:
	void smartFocusOutEvent(const QString& text);

protected:
	void focusOutEvent(QFocusEvent* e) override;
};