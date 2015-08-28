#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QList>
#include <QHash>
#include <QDate>
#include <QTime>
#include <QStringList>
#include <QLoggingCategory>
#include "server_global.h"
#include "variable.h"

Q_DECLARE_LOGGING_CATEGORY(SERVER)

class SERVERSHARED_EXPORT Server : public QObject
{
    Q_OBJECT

public:
    Server();
    ~Server();

public slots:
    inline void setCoordinate(QHash<float, QList<Spot3DCoordinate> > spot3D){m_spot3D = spot3D;}
    inline void setSpotOrder(QHash<float, QList<int> > spotOrder){m_spotOrder = spotOrder;}
    inline void setParameter(SpotSonicationParameter param){m_parameter = param;}

    void sendPlanHash();
    void sendCommandStart();
    void sendCommandStop();
    void sendCommandPause();
    void sendCommandResume();
    void sendCommand(cmdType);

private slots:
    void connectServer();    // Connect to client
    void displayError(QAbstractSocket::SocketError);    // Display error

    void convertSpot();
    QString writeSendInfo();
    void readSendBack();
    void writtenBytes(qint64);

signals:
    error_sendBackCheck();
    error_sendCheck();

private:
    QTcpSocket *m_tcpServer;
    QByteArray m_outBlock;
    QByteArray m_inBlock;
    QStringList m_cmdList;

    qint64 m_totalBytes;    // Total bytes to send for this send progress
    qint64 m_writtenBytes;

    QHash<float, QList<Spot3DCoordinate> > m_spot3D;
    QHash<float, QList<float> > m_hashX;
    QHash<float, QList<float> > m_hashY;
    QHash<float, QList<float> > m_hashZ;
    QHash<float, QList<int> > m_spotOrder;
    SpotSonicationParameter m_parameter;

    QDate m_date;
    QTime m_time;
    int m_sendTimeNum;
    QString m_receivedInfo;

    void setCmdString();
};


#endif // SERVER_H
