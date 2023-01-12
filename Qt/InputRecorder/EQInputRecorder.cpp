#include "EQInputRecorder.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QIcon>

EQInputRecorder::EQInputRecorder(QWidget *parent)
	: QMainWindow(parent), currentRecordingText()
{
	QWidget* centralWidget{ new QWidget };
	QVBoxLayout* centralLayout{ new QVBoxLayout };

	QHBoxLayout* bottomLayout{ new QHBoxLayout };
	bottomLayout->addWidget(initRecordingGroupBox());
	bottomLayout->addWidget(initPlayingGroupBox());

	centralLayout->addWidget(initTopGroupBox());
	centralLayout->addLayout(bottomLayout);
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("inputRecorder.png"));
}

QGroupBox* EQInputRecorder::initTopGroupBox()
{
	QGroupBox* currentRecordingGroupBox{ new QGroupBox("Recording selection") };
	QHBoxLayout* groupBoxLayout{ new QHBoxLayout };
	QLabel* currentRecordingLabel{ new QLabel("Current recording :") };
	currentRecordingText = new QLabel("None");

	groupBoxLayout->addWidget(currentRecordingLabel);
	groupBoxLayout->addWidget(currentRecordingText);
	currentRecordingGroupBox->setLayout(groupBoxLayout);
	return currentRecordingGroupBox;
}

QGroupBox* EQInputRecorder::initRecordingGroupBox()
{
	QGroupBox* recordingGroupBox{ new QGroupBox("Record") };
	QVBoxLayout* groupBoxLayout{ new QVBoxLayout };
	QLabel* currentRecordingLabel{ new QLabel("Current recording :") };
	currentRecordingText = new QLabel("None");

	groupBoxLayout->addWidget(currentRecordingLabel);
	groupBoxLayout->addWidget(currentRecordingText);
	recordingGroupBox->setLayout(groupBoxLayout);
	return recordingGroupBox;
}

QGroupBox* EQInputRecorder::initPlayingGroupBox()
{
	QGroupBox* currentRecordingGroupBox{ new QGroupBox("Playback") };
	QVBoxLayout* groupBoxLayout{ new QVBoxLayout };
	QLabel* currentRecordingLabel{ new QLabel("Current recording :") };
	currentRecordingText = new QLabel("None");

	groupBoxLayout->addWidget(currentRecordingLabel);
	groupBoxLayout->addWidget(currentRecordingText);
	currentRecordingGroupBox->setLayout(groupBoxLayout);
	return currentRecordingGroupBox;
}

EQInputRecorder::~EQInputRecorder() {}