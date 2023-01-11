#include "EQInputRecorder.h"
#include <QBoxLayout>
#include <QLabel>



EQInputRecorder::EQInputRecorder(QWidget *parent)
	: QMainWindow(parent)
{
	QVBoxLayout* centralLayout{ new QVBoxLayout };
	QWidget* centralWidget{ new QWidget };
	
	QLabel* test{ new QLabel("Testing") };
	centralLayout->addWidget(test);

	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
}

EQInputRecorder::~EQInputRecorder()
{}
