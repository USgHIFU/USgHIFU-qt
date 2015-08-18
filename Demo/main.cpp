#include "SmtpMime"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // First we need to create an SmtpClient object
    // We will use the 163 mail's smtp server (smtp.163.com, port 465, ssl)

    SmtpClient smtp("smtp.163.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and password
    // for smtp authentification.

    smtp.setUser("jethroflying@163.com");
    smtp.setPassword("usghifu_123");

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

    message.addPart(new MimeAttachment(new QFile("../Hackthon(20150726).doc")));

    // Now we can send the mail

    if (!smtp.connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
    }else
    {
        qDebug() << "Connection OK.";
    }

    if (!smtp.login()) {
        qDebug() << "Failed to login!" << endl;
    }else
    {
        qDebug() << "Login successfully.";
    }

    if (!smtp.sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
    }else
    {
        qDebug() << "Sending mail successfully.";
    }

    smtp.quit();

    return a.exec();
}
