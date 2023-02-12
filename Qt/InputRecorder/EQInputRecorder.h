#pragma once

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QThread>
#include "EQInputRecorderWorker.h"

class EQInputRecorder : public QMainWindow
{
	Q_OBJECT

public:
	EQInputRecorder(QWidget *parent = nullptr);
	~EQInputRecorder();

private:
	QGroupBox* initOutputGroupBox();
	QGroupBox* initRecordingGroupBox();
	QGroupBox* initPlayingGroupBox();

	EQInputRecorderWorker* worker;
	QThread workerThread;
};