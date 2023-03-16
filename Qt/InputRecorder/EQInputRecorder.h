#pragma once

#include <QMainWindow>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include "EQInputRecorderWorker.h"

class EQInputRecorder : public QMainWindow
{
	Q_OBJECT

public:
	EQInputRecorder(QWidget *parent = nullptr);
	~EQInputRecorder();

private slots:
	void bringWindowInFront();
	void disableButtons();
	void enableButtons();

private:
	QGroupBox* initOutputGroupBox();
	QGroupBox* initRecordingGroupBox();
	QGroupBox* initPlayingGroupBox();

	QPushButton* recordingButton;
	QPushButton* playbackButton;

	EQInputRecorderWorker* worker;
	QThread workerThread;
};