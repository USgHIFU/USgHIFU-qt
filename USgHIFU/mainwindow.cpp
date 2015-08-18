#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // First we need to create an SmtpClient object
    // We will use the 163 mail's smtp server (smtp.163.com, port 465, ssl)

    smtp = new SmtpClient("smtp.163.com", 465, SmtpClient::SslConnection);

    // The name of the attachment file
    attachmentFileName = "../Hackthon(20150726).doc";

    monitor = new PerformanceMonitor(this);

    btnSend = new QPushButton("send",this);
    btnShutDownPC = new QPushButton("shut down",this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(btnSend);
    layout->addWidget(btnShutDownPC);

    statusInfo = new QLabel(this);
    memLoadInfo = new QLabel(this);
    availPhysInfo = new QLabel(this);
    statusBar()->addWidget(statusInfo);
    statusBar()->addWidget(memLoadInfo);
    statusBar()->addWidget(availPhysInfo);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(btnSend,SIGNAL(clicked(bool)),SLOT(notificationUpdate()));
    connect(btnShutDownPC,SIGNAL(clicked(bool)),SLOT(shutDownPC()));
    connect(monitor,SIGNAL(memLoadUpdate(DWORD)),SLOT(memLoadUpdate(DWORD)));
    connect(monitor,SIGNAL(memAvailPhysUpdate(DWORDLONG)),SLOT(availPhysUpdate(DWORDLONG)));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::sendMail()
{
    // Now we create a MimeMessage object. This is the email.

    MimeMessage message;

    EmailAddress sender("jethroflying@163.com", "USgHIFU");
    message.setSender(&sender);

    EmailAddress to("xiangji@sjtu.edu.cn", "JI Xiang");
    message.addRecipient(&to);

    message.setSubject("Notification for USgHIFU");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText("Hi,\nThis is a email notification for test.\n");

    // Now add it to the mail

    message.addPart(&text);

    // Now add an attachment to the email.
    // First we create a MimeAttachment object.

    message.addPart(new MimeAttachment(new QFile(attachmentFileName)));

    // Now we can send the mail

    if (loginAccount())
    {
        statusInfo->setText("Login successfully.");
    }else
    {
        statusInfo->setText("Failed to login!");
        return false;
    }

    if (!smtp->sendMail(message))
    {
        qDebug() << "Failed to send mail!" << endl;
        statusInfo->setText("Failed to send mail!");
        return false;
    }else
    {
        qDebug() << "Sending mail successfully.";
        statusInfo->setText("Sending mail successfully.");
    }

    smtp->quit();
    return true;
}

bool MainWindow::loginAccount()
{
    // We need to set the username (your email address) and password
    // for smtp authentification.

    smtp->setUser("jethroflying@163.com");
    smtp->setPassword("usghifu_123");


    if (!smtp->connectToHost())
    {
        qDebug() << "Failed to connect to host!" << endl;
        return false;
    }else
    {
        qDebug() << "Connection OK.";
    }

    if (!smtp->login())
    {
        qDebug() << "Failed to login!" << endl;
        return false;
    }else
    {
        qDebug() << "Login successfully.";
        return true;
    }
}

void MainWindow::notificationUpdate()
{
    sendMail();
}

void MainWindow::shutDownPC()
{
    if (monitor->shutDownPC())
    {
        qDebug() << "Shutting down computer.";
    }else
    {
        qDebug() << "Cannot shut down computer.";
    }
}

void MainWindow::memLoadUpdate(DWORD memLoad)
{
    memLoadInfo->setText(QString("Memory used ratio: %1%\n.").arg(memLoad));
}

void MainWindow::availPhysUpdate(DWORDLONG availPhys)
{
    availPhysInfo->setText(QString("Available memory: %1\n.").arg(availPhys));
}
