#include <QFile>
#include <QTextStream>
#include <QDateTime>

void logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QDateTime currentTime = QDateTime::currentDateTime();

    QByteArray log = currentTime.toString("yyyy-MM-dd hh:mm:ss ").toLocal8Bit();
    QByteArray Log;

    switch(type)
    {
        case QtDebugMsg:
            log += QString("%1\r\n").arg(msg);
            break;
        case QtWarningMsg:
            log += QString("Warning: %1\r\n").arg(msg);
            Log += QString("%1\r\n").arg(msg);
            break;
        case QtCriticalMsg:
            log += QString("Critical: %1\r\n").arg(msg);
            break;
        case QtFatalMsg:
            log += QString("Fatal: %1\r\n").arg(msg);
            abort();
    }
    QString fileName = "../LoggingRecord.log";
    QFile outFile(fileName);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream textStream(&outFile);
        textStream << log << endl;
        outFile.close();
    }

    QString warningFile = "../WarningRecord.log";
    QFile outfile(warningFile);
    if (outfile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream textStream(&outfile);
        textStream << Log << endl;
        outfile.close();
    }
}
