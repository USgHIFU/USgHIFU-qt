#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "treatsession.h"
#include "client.h"

class QLineEdit;
class QPushButton;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void btnStartClick();
    void btnStopClick();
    void btnPauseClick();
    void btnResumeClick();
    void btnStartPAClicked();
    void btnStartDOClicked();

private:
    TreatSession* session;
    Client* m_client;

    QLineEdit* totalTime;
    QLineEdit* period;
    QLineEdit* dutyCycle;
    QLineEdit* coolingTime;

    QPushButton* start;
    QPushButton* stop;
    QPushButton* pause;
    QPushButton* resume;
    QPushButton* startPA;
    QPushButton* startDO;

    QLabel* status;
};

#endif // MAINWINDOW_H
