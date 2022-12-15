#pragma once

#include <QObject>
#include "../../Utilities/EQKeyboardListener/EQKeyboardListener.h"

class EQAutoClickerWorker  : public QObject
{
	Q_OBJECT

public:
	EQAutoClickerWorker(QObject *parent);
	~EQAutoClickerWorker();
private:
	bool active;
};
