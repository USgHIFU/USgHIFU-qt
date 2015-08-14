#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    session = new ServerPlan(this);

    totalTime = new QLineEdit(this);
    totalTime->setText("12");
    period = new QLineEdit(this);
    period->setText("500");
    dutyCycle = new QLineEdit(this);
    dutyCycle->setText("60");
    coolingTime = new QLineEdit(this);
    coolingTime->setText("10");

    QHBoxLayout* editLayout = new QHBoxLayout;
    editLayout->addWidget(totalTime);
    editLayout->addWidget(period);
    editLayout->addWidget(dutyCycle);
    editLayout->addWidget(coolingTime);

    start = new QPushButton(this);
    start->setText("start");
    stop = new QPushButton(this);
    stop->setText("stop");
    pause = new QPushButton(this);
    pause->setText("pause");
    resume = new QPushButton(this);
    resume->setText("resume");
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(start);
    btnLayout->addWidget(stop);
    btnLayout->addWidget(pause);
    btnLayout->addWidget(resume);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addLayout(btnLayout);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    status = new QLabel(this);
    statusBar()->addWidget(status);


    SpotSonicationParam param = {VOLTAGE,
                                 totalTime->text().toInt(),
                                 period->text().toInt(),
                                 dutyCycle->text().toInt(),
                                 coolingTime->text().toInt()};
    session->setSonicationParam(param);

    connect(start,SIGNAL(clicked(bool)),SLOT(btnStartClick()));
    connect(stop,SIGNAL(clicked(bool)),SLOT(btnStopClick()));
    connect(pause,SIGNAL(clicked(bool)),SLOT(btnPauseClick()));
    connect(resume,SIGNAL(clicked(bool)),SLOT(btnResumeClick()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::btnStartClick()
{
    session->startSession();
    status->setText("The treatment session is started.");
}

void MainWindow::btnStopClick()
{
    session->stopSession();
    status->setText("The treatment session is stopped.");
}

void MainWindow::btnPauseClick()
{
    session->pauseSession();
    status->setText("The treatment session is paused.");
}

void MainWindow::btnResumeClick()
{
    session->resumeSession();
    status->setText("The treatment session is resumed.");
}
