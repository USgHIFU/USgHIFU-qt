#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QPushButton;
class QLabel;

#include <QMainWindow>
#include "SmtpMime"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void notificationUpdate();

private:
    SmtpClient* smtp;
    QString attachmentFileName;

    QPushButton* btnSend;
    QLabel* statusInfo;

    bool loginAccount();
    bool sendMail();
};

#endif // MAINWINDOW_H
