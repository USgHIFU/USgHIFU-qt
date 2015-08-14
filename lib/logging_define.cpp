#include <QFile>
#include <QTextStream>
#include <QDateTime>

void writeLogFile(QByteArray log,QString fileName);

void logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QString warningFileName = "../WarningRecord.log";
    QDateTime currentTime = QDateTime::currentDateTime();

    QByteArray log = currentTime.toString("yyyy-MM-dd hh:mm:ss ").toLocal8Bit();

    switch(type)
    {
    case QtDebugMsg:
        log += QString("%1\r\n").arg(msg);
        break;
    case QtWarningMsg:
        log += QString("Warning: %1\r\n").arg(msg);

        writeLogFile(log,warningFileName);
        break;
    case QtCriticalMsg:
        log += QString("Critical: %1\r\n").arg(msg);
        break;
    case QtFatalMsg:
        log += QString("Fatal: %1\r\n").arg(msg);
        abort();
    }

    QString fileName = "../LoggingRecord.log";
    writeLogFile(log,fileName);
}

void writeLogFile(QByteArray log,QString fileName)
{
    QFile outFile(fileName);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream textStream(&outFile);
        textStream << log << endl;
        outFile.close();
    }
}
