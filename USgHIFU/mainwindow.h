#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QPushButton;
class QLabel;

#include <QMainWindow>
#include "SmtpMime"
#include "performancemonitor.h"

Q_DECLARE_LOGGING_CATEGORY(MAIL)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void notificationUpdate();
    void memLoadUpdate(DWORD memLoad);
    void availPhysUpdate(DWORDLONG availPhys);
    void shutDownPC();

private:
    SmtpClient* smtp;
    QString attachmentFileName;
    PerformanceMonitor* monitor;

    enum MailAction
    {
        ConnectToHost,
        LoginAccount,
        SendMail
    };

    QPushButton* btnSend;
    QPushButton* btnShutDownPC;
    QLabel* statusInfo;
    QLabel* memLoadInfo;
    QLabel* availPhysInfo;

    bool loginAccount();
    bool sendMail();
};

#endif // MAINWINDOW_H
