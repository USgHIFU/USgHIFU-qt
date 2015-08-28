#ifndef POWERAMP_H
#define POWERAMP_H

#include "poweramp_global.h"
#include <QObject>
#include <QByteArray>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QLoggingCategory>
#include "constant.h"

Q_DECLARE_LOGGING_CATEGORY(SerialPort_connection)
Q_DECLARE_LOGGING_CATEGORY(Test_module)

class POWERAMPSHARED_EXPORT PowerAmp : public QObject
{
    Q_OBJECT

public:
    PowerAmp(QObject *parent = 0);
    ~PowerAmp();
    bool resetSinglePowerAmp(int PowerAmpId);
    bool resetAllPowerAmp();
    bool startSinglePowerAmp(int PowerAmpId, double Volt);
    bool startAllPowerAmp(double Volt);
    double echoPowerAmp(int PowerAmpId);
    QSerialPort* m_serialPort;

signals:
    void errorOccur(QString errorString);

private:
    enum PowerAmpAction{RESET,START,ECHO};
    QByteArray m_bytesRead;
    QList<int> m_errorPowerAmpIdForReset;
    QList<int> m_errorPowerAmpIdForStart;
    QSerialPort* identifyProbe();
    int validatePowerAmp(int ID);
    double validateVoltage(double Volt);
    bool validateEcho(QByteArray BytesEcho, QByteArray BytePowerAmpId);
    QByteArray getPowerAmpIdByte(int ID);
    QByteArray getVoltageBytes(PowerAmpAction Action, double Volt);
    QByteArray getCheckByte(QByteArray BytePowerAmpId, QByteArray BytesVolt );
    bool checkReadBytes(QByteArray BytesRead, QByteArray BytesSend);
    double bytes2voltage(QByteArray BytesEcho);

private slots:
    void handleError(QSerialPort::SerialPortError error);
};

#endif // POWERAMP_H
