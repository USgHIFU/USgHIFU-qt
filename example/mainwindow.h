#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QLineEdit;
class QPushButton;
class QLabel;

#include <QMainWindow>
#include "serverplan.h"

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

private:
    ServerPlan* session;

    QLineEdit* totalTime;
    QLineEdit* period;
    QLineEdit* dutyCycle;
    QLineEdit* coolingTime;

    QPushButton* start;
    QPushButton* stop;
    QPushButton* pause;
    QPushButton* resume;

    QLabel* status;
};

#endif // MAINWINDOW_H
