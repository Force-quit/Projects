#pragma once

#include <QLineEdit>
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
};
