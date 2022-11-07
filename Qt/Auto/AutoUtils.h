#pragma once

#include <QMainWindow>
#include "ui_AutoUtils.h"

class AutoUtils : public QMainWindow
{
	Q_OBJECT

public:
	AutoUtils(QWidget *parent = nullptr);
	~AutoUtils();

private:
	Ui::AutoUtilsClass ui;
	const std::string CONFIG_PATH{ "Configs" };
};
