#ifndef CLIENT_H
#define CLIENT_H


#include "variable.h"
#include "client_global.h"

#include <QObject>
#include <QtNetwork>
#include <QHash>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(CLIENT)


class CLIENTSHARED_EXPORT Client : public QObject
{
    Q_OBJECT

public:
    Client();
    ~Client();

signals:
    commandStart();
    commandStop();
    commandPause();
    commandResume();

private:
    QTcpServer m_tcpClient;    // Server object
    QTcpSocket *m_tcpClientConnection;    // Socket object
    QString m_ipAddress;    // IP information

    QByteArray m_outBlock;    // Data buffer for write
    QDataStream out;

    qint64 m_totalBytes;    // Total bytes of data to send
    qint64 m_bytesReceived;    // Length of received data
    QHash<float, QList<Spot3DCoordinate> > m_spot3D;    // Save spot coordinates data
    QHash<float, QList<float> > m_hashX;
    QHash<float, QList<float> > m_hashY;
    QHash<float, QList<float> > m_hashZ;
    QHash<float, QList<int> > m_spotOrder;
    SpotSonicationParameter m_parameter;
    qint64 m_command;

private slots:
    void acceptConnection();    // Build connection
    void displayError(QAbstractSocket::SocketError socketError);    //Display the error
    QString getLocalIP();

    void convertSpot();
    void readHead();
    void receivePlanHash();
    void receiveCommand();
    void bytes(qint64 byteswrite);

    void varInit();

public slots:
    void listen();    // Start to listen port

    QHash<float, QList<Spot3DCoordinate> > getCoordinate();
    QHash<float, QList<int> > getSpotOrder();
    SpotSonicationParameter getParameter();
};

#endif // CLIENT_H
