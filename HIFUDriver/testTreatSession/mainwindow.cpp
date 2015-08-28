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
    session = new TreatSession(this);
    m_client = new Client;
    m_client->listen();

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
    startPA = new QPushButton(this);
    startPA->setText("StartPA");
    startDO = new QPushButton(this);
    startDO->setText("StartDO");
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(start);
    btnLayout->addWidget(stop);
    btnLayout->addWidget(pause);
    btnLayout->addWidget(resume);
    btnLayout->addWidget(startPA);
    btnLayout->addWidget(startDO);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addLayout(btnLayout);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    status = new QLabel(this);
    statusBar()->addWidget(status);

    SpotSonicationParameter param = {VOLTAGE,
                                 totalTime->text().toInt(),
                                 period->text().toInt(),
                                 dutyCycle->text().toInt(),
                                 coolingTime->text().toInt()};
    session->setSonicationParam(param);

    connect(start,SIGNAL(clicked(bool)),SLOT(btnStartClick()));
    connect(stop,SIGNAL(clicked(bool)),SLOT(btnStopClick()));
    connect(pause,SIGNAL(clicked(bool)),SLOT(btnPauseClick()));
    connect(resume,SIGNAL(clicked(bool)),SLOT(btnResumeClick()));
    connect(m_client,SIGNAL(commandStart()),start,SIGNAL(clicked()));
    connect(m_client,SIGNAL(commandStop()),stop,SIGNAL(clicked()));
    connect(startPA,SIGNAL(clicked()),SLOT(btnStartPAClicked()));
    connect(startDO,SIGNAL(clicked()),SLOT(btnStartDOClicked()));
}

MainWindow::~MainWindow()
{
//    session->~TreatSession();
}

void MainWindow::btnStartClick()
{
    session->setSpots(m_client->getCoordinate());
    session->setSonicationParam(m_client->getParameter());

    session->start();
    status->setText("The treatment session is started.");
}

void MainWindow::btnStopClick()
{
    session->stop();
    status->setText("The treatment session is stopped.");
}

void MainWindow::btnPauseClick()
{
    session->pause();
    status->setText("The treatment session is paused.");
}

void MainWindow::btnResumeClick()
{
    session->resume();
    status->setText("The treatment session is resumed.");
}

void MainWindow::btnStartPAClicked()
{
    session->testPA();
}

void MainWindow::btnStartDOClicked()
{
    session->testDOController();
}
