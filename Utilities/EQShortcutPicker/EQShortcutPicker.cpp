#include "EQShortcutPicker.h"
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "EQShortcutPickerWorker.h"
#include <QPushButton>

EQShortcutPicker::EQShortcutPicker(QString labelText, QWidget *parent)
	: QWidget(parent), workerThread(), changeShortcutButton()
{
	QHBoxLayout* centralLayout{ new QHBoxLayout };
	
	QLabel* label{ new QLabel(labelText) };
	shortcutText = new QLabel(EQShortcutPickerWorker::DEFAULT_SHORTCUT);
	changeShortcutButton = new QPushButton("Change");

	centralLayout->addWidget(label);
	centralLayout->addWidget(shortcutText);
	centralLayout->addWidget(changeShortcutButton);


	EQShortcutPickerWorker* worker{ new EQShortcutPickerWorker };
	connect(changeShortcutButton, &QPushButton::clicked, changeShortcutButton, &QWidget::setEnabled);
	connect(changeShortcutButton, SIGNAL(clicked()), this, SIGNAL(startedListening()));
	connect(changeShortcutButton, &QPushButton::clicked, worker, &EQShortcutPickerWorker::startListening);
	
	connect(worker, &EQShortcutPickerWorker::shortcutChanged, shortcutText, &QLabel::setText);

	connect(worker, &EQShortcutPickerWorker::shortcutSelected, this, &EQShortcutPicker::shortcutChosen);

	connect(worker, &EQShortcutPickerWorker::shortcutFinalised, this, &EQShortcutPicker::shortcutChanged);
	

	QThread::currentThread()->setObjectName("Main thread");
	workerThread.setObjectName("Worker thread");
	worker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	workerThread.start();

	setLayout(centralLayout);
}

void EQShortcutPicker::shortcutChosen()
{
	changeShortcutButton->setEnabled(true);
}


EQShortcutPicker::~EQShortcutPicker()
{
	workerThread.quit();
	workerThread.wait();
}