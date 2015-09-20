#ifndef POWERAMP_H
#define POWERAMP_H

#include "poweramp_global.h"
#include "constant.h"
#include "macro.h"

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QList>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(PA)
Q_DECLARE_LOGGING_CATEGORY(PA_TEST)

class POWERAMPSHARED_EXPORT PowerAmp : public QObject
{
    Q_OBJECT
public:
    PowerAmp(QObject* parent = 0);
    ~PowerAmp();

    enum ACTION
    {
        RESET,
        START,
        ECHO_VOLT,
        ECHO_TEMP
    };

    bool exist();

    void startAll2(VOLT volt);
    VOLT echoVolt(int id);
    DEGREE echoTemp(int id);

    void testModule();

public slots:
    bool resetSingle(int id);
    bool resetAll();
    void resetAll2();
    bool startSingle(int id, VOLT volt);
    bool startAll(VOLT volt);

signals:
    void error(QString errorString);

private:

    QSerialPort* m_serialPort;
    bool m_existSerialPort;

    QByteArray m_baRead;

    QList<int> m_errorId4Start;
    QList<int> m_errorId4Reset;

    QSerialPort* identify();
    bool open();
    void close();

    int validateId(int id);
    VOLT validateVolt(VOLT volt);

    QByteArray computeBaId(int id);
    QByteArray computeBaVolt(ACTION action, VOLT volt);
    QByteArray computeBaCheck(QByteArray baId,QByteArray baVolt);
    VOLT ba2volt(QByteArray baEcho);
    DEGREE ba2temp(QByteArray baEcho);

    bool checkReceivedBytes(QByteArray baReceive, QByteArray baSend);

    //  TEST MODULE
    void testStartSingle();
    void testStartAll();
    void testResetSingle();
    void testResetAll();
    void testEchoVolt();
    void testEchoTemp();
    int genRanId();
    VOLT genRanVolt();
    int genRandomNum();
    //  TEST MODULE

private slots:
    void handleError(QSerialPort::SerialPortError serialError);
};

#endif // POWERAMP_H
