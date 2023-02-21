#include "EQInputRecorder.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QIcon>
#include <QPushButton>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include "EQInputRecorderWorker.h"
#include "../../Utilities/EQShortcutListener/EQShortcutListener.h"

EQInputRecorder::EQInputRecorder(QWidget *parent)
	: QMainWindow(parent), workerThread(), worker{new EQInputRecorderWorker}
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

	QPushButton* startRecording{ new QPushButton("Start recording") };
	connect(startRecording, &QPushButton::clicked, worker, &EQInputRecorderWorker::startRecording);

	//TODO
	EQShortcutListener* stopRecordingListener{ new EQShortcutListener("Stop recording shortcut : ") };
	
	groupBoxLayout->addWidget(startRecording);
	recordingGroupBox->setLayout(groupBoxLayout);
	return recordingGroupBox;
}

QGroupBox* EQInputRecorder::initPlayingGroupBox()
{
	QGroupBox* currentRecordingGroupBox{ new QGroupBox("Playback") };
	QVBoxLayout* groupBoxLayout{ new QVBoxLayout };
	QPushButton* startPlayback{ new QPushButton("Start playback") };
	connect(startPlayback, &QPushButton::clicked, worker, &EQInputRecorderWorker::startPlayback);

	groupBoxLayout->addWidget(startPlayback);
	currentRecordingGroupBox->setLayout(groupBoxLayout);
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