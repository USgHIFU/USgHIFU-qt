#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

void printSeparator()
{
    qDebug() << "=========================================================" << endl;

}

void writeFile(QString fileName,QByteArray record)
{
    QFile logFile(fileName);
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream logRecord(&logFile);
        logRecord << record << endl;
        logFile.close();
    }
}

void logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QDateTime currentTime = QDateTime::currentDateTime();
    QString fileName = "../" + currentTime.toString("yyyy-MM-dd") + " record.log";
    QString warningFileName = "../" + currentTime.toString("yyyy-MM-dd") + " warning.log";
    QString errorFileName = "../" + currentTime.toString("yyyy-MM-dd") + " error.log";

    QByteArray record = currentTime.toString("hh:mm:ss ").toLocal8Bit();

    switch(type)
    {
    case QtDebugMsg:
        record += QString("%1\r\n").arg(msg);
        break;
    case QtWarningMsg:
        record += QString("Warning: %1\r\n").arg(msg);
        writeFile(warningFileName,record);
        break;
    case QtCriticalMsg:
        record += QString("Error: %1\r\n").arg(msg);
        writeFile(errorFileName,record);
        break;
    case QtFatalMsg:
        record += QString("Fatal: %1\r\n").arg(msg);
        abort();
    }
    writeFile(fileName,record);
}
