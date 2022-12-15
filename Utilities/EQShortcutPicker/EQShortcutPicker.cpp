#include "EQShortcutPicker.h"
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "EQShortcutPickerWorker.h"
#include <QPushButton>

EQShortcutPicker::EQShortcutPicker(QString labelText, QWidget *parent)
	: QWidget(parent), workerThread()
{
	QHBoxLayout* centralLayout{ new QHBoxLayout };
	
	QLabel* label{ new QLabel(labelText) };
	QLabel* shortcutText{ new QLabel(EQShortcutPickerWorker::DEFAULT_SHORTCUT) };
	QPushButton* changeShortcutButton{ new QPushButton("Change") };

	centralLayout->addWidget(label);
	centralLayout->addWidget(shortcutText);
	centralLayout->addWidget(changeShortcutButton);


	EQShortcutPickerWorker* worker{ new EQShortcutPickerWorker };
	connect(changeShortcutButton, &QPushButton::clicked, changeShortcutButton, &QWidget::setEnabled);
	connect(changeShortcutButton, &QPushButton::clicked, worker, &EQShortcutPickerWorker::startListening);
	
	connect(worker, &EQShortcutPickerWorker::shortcutChanged, shortcutText, &QLabel::setText);
	connect(worker, &EQShortcutPickerWorker::shortcutSelected, [this, changeShortcutButton](QVector<int> virtualKeys) {
		changeShortcutButton->setEnabled(true);
		emit shortcutChanged(virtualKeys);
	});

	worker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	workerThread.start();

	setLayout(centralLayout);
}

EQShortcutPicker::~EQShortcutPicker()
{
	workerThread.quit();
	workerThread.wait();
}