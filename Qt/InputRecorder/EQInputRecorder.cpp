#include "EQInputRecorder.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QIcon>
#include <QPushButton>
#include <QCheckBox>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include "EQInputRecorderWorker.h"
#include "../../Utilities/EQShortcutListener/EQShortcutListener.h"

EQInputRecorder::EQInputRecorder(QWidget *parent)
	: QMainWindow(parent), workerThread(), worker{new EQInputRecorderWorker}, recordingButton{}, playbackButton{}
{
	worker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(worker, &EQInputRecorderWorker::finishedRecording, this, &EQInputRecorder::bringWindowInFront);
	connect(worker, &EQInputRecorderWorker::finishedPlayback, this, &EQInputRecorder::bringWindowInFront);
	workerThread.start();


	QWidget* centralWidget{ new QWidget };
	QVBoxLayout* centralLayout{ new QVBoxLayout };

	QGroupBox* ouputGroupBox{ initOutputGroupBox() };

	QHBoxLayout* bottomLayout{ new QHBoxLayout };
	bottomLayout->addWidget(initRecordingGroupBox());
	bottomLayout->addWidget(initPlayingGroupBox());

	centralLayout->addWidget(ouputGroupBox);
	centralLayout->addLayout(bottomLayout);
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("inputRecorder.png"));
}


void EQInputRecorder::disableButtons()
{
	recordingButton->setEnabled(false);
	playbackButton->setEnabled(false);
}

void EQInputRecorder::enableButtons()
{
	playbackButton->setEnabled(true);
	recordingButton->setEnabled(true);
}

QGroupBox* EQInputRecorder::initOutputGroupBox()
{
	QGroupBox* outputGroupBox{ new QGroupBox("Output") };
	QHBoxLayout* groupBoxLayout{ new QHBoxLayout };
	groupBoxLayout->setAlignment(Qt::AlignLeft);

	QLabel* outputLabel{ new QLabel("Current status :") };
	QLabel* ouputText{ new QLabel("Inactive") };
	connect(worker, &EQInputRecorderWorker::textChanged, ouputText, &QLabel::setText);

	groupBoxLayout->addWidget(outputLabel);
	groupBoxLayout->addWidget(ouputText);
	outputGroupBox->setLayout(groupBoxLayout);
	return outputGroupBox;
}

QGroupBox* EQInputRecorder::initRecordingGroupBox()
{
	QGroupBox* recordingGroupBox{ new QGroupBox("Record") };
	QVBoxLayout* groupBoxLayout{ new QVBoxLayout };
	groupBoxLayout->setAlignment(Qt::AlignCenter);

	recordingButton = new QPushButton("Start recording");
	QLabel* recordingShortcutLabel{ new QLabel("Stop recording : ESC") };
	
	groupBoxLayout->addWidget(recordingButton);
	groupBoxLayout->addWidget(recordingShortcutLabel);
	recordingGroupBox->setLayout(groupBoxLayout);

	connect(recordingButton, &QPushButton::clicked, worker, &EQInputRecorderWorker::startRecording);
	connect(recordingButton, &QPushButton::clicked, this, &EQInputRecorder::disableButtons);
	connect(worker, &EQInputRecorderWorker::finishedRecording, this, &EQInputRecorder::enableButtons);

	return recordingGroupBox;
}

QGroupBox* EQInputRecorder::initPlayingGroupBox()
{
	QGroupBox* currentRecordingGroupBox{ new QGroupBox("Playback") };
	QVBoxLayout* groupBoxLayout{ new QVBoxLayout };
	groupBoxLayout->setAlignment(Qt::AlignCenter);
	
	playbackButton = new QPushButton("Start playback");
	QLabel* playbackShortcutLabel{ new QLabel("Stop playback : ESC") };
	QCheckBox* loopCheckbox{ new QCheckBox("Looping") };

	groupBoxLayout->addWidget(playbackButton);
	groupBoxLayout->addWidget(loopCheckbox);
	groupBoxLayout->addWidget(playbackShortcutLabel);
	currentRecordingGroupBox->setLayout(groupBoxLayout);

	connect(playbackButton, &QPushButton::clicked, worker, &EQInputRecorderWorker::startPlayback);
	connect(loopCheckbox, &QCheckBox::stateChanged, [this](int state) {
		worker->setPlaybackLoop(state);
	});
	connect(worker, &EQInputRecorderWorker::canceledPlaybackLoop, [loopCheckbox]() {
		loopCheckbox->setCheckState(Qt::Unchecked);
	});
	connect(playbackButton, &QPushButton::clicked, this, &EQInputRecorder::disableButtons);
	connect(worker, &EQInputRecorderWorker::finishedPlayback, this, &EQInputRecorder::enableButtons);


	return currentRecordingGroupBox;
}

void EQInputRecorder::bringWindowInFront()
{
	activateWindow();
}

EQInputRecorder::~EQInputRecorder() 
{
	workerThread.quit();
	workerThread.wait();
}