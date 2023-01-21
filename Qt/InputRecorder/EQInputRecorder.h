#pragma once

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>

class EQInputRecorder : public QMainWindow
{
	Q_OBJECT

public:
	EQInputRecorder(QWidget *parent = nullptr);
	~EQInputRecorder();

private:
	QLabel* currentRecordingText;

	QGroupBox* initTopGroupBox();
	QGroupBox* initRecordingGroupBox();
	QGroupBox* initPlayingGroupBox();
};
