#ifndef SERVER_H
#define SERVER_H


#include "server_global.h"
#include "variable.h"

#include <QObject>
#include <QtNetwork>
#include <QList>
#include <QHash>
#include <QDate>
#include <QTime>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(SERVER)


class SERVERSHARED_EXPORT Server : QObject
{
    Q_OBJECT

private:
    QTcpSocket *m_tcpServer;
    QByteArray m_outBlock;
    QByteArray m_inBlock;

    qint64 m_totalBytes;    // Total bytes to send for this send progress
    qint64 m_writtenBytes;

    QHash<float, QList<Spot3DCoordinate> > m_spot3D;
    QHash<float, QList<float> > m_hashX;
    QHash<float, QList<float> > m_hashY;
    QHash<float, QList<float> > m_hashZ;
    QHash<float, QList<int> > m_spotOrder;
    //QHash<QString, int> m_parameter;
    SpotSonicationParameter m_parameter;

    QDate m_date;
    QTime m_time;
    int m_sendTimeNum;
    QString m_receivedInfo;

public:
    Server();
    ~Server();

signals:
    error_sendBackCheck();
    error_sendCheck();

private slots:
    void connectServer();    // Connect to client
    void displayError(QAbstractSocket::SocketError);    // Display error

    void convertSpot();
    QString writeSendInfo();
    void readSendBack();
    void writtenBytes(qint64);


public slots:
    void setCoordinate(QHash<float, QList<Spot3DCoordinate> > spot3D);
    void setSpotOrder(QHash<float, QList<int> > spotOrder);
    void setParameter(SpotSonicationParameter parameter);

    void sendPlanHash();
    void sendCommandStart();
    void sendCommandStop();
    void sendCommandPause();
    void sendCommandResume();
};


#endif // SERVER_H
