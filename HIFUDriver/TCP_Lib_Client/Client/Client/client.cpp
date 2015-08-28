#include <QObject>
#include <QtNetwork>
#include <QList>
#include <qDebug>
#include <QHostInfo>
#include "client.h"

Q_LOGGING_CATEGORY(CLIENT, "CLIENT")

Client::Client()
{
// Initialize variables and connections
    QDataStream in(m_tcpClientConnection);
    in.setVersion(QDataStream::Qt_4_6);

    m_totalBytes = 0;

    m_ipAddress = getLocalIP();
    qDebug() << "IP Address:" << m_ipAddress;
}

Client::~Client()
{
}


// Start to listen
void Client::listen()
{
    m_bytesReceived = 0;

    QHostAddress ipAddress(m_ipAddress.toInt());
    if(!m_tcpClient.listen(ipAddress, 6666))
    {
        qCWarning(CLIENT()) << CLIENT().categoryName() << ":" << m_tcpClient.errorString();
        m_tcpClient.close();
        return;
    }
    qDebug() << "Listen OK";

    connect(&m_tcpClient, SIGNAL(newConnection()) ,
            this, SLOT(acceptConnection()));    // Send newConnection() signal when a new connection is detected
}


// Accept new connection
void Client::acceptConnection()
{
    m_tcpClientConnection = m_tcpClient.nextPendingConnection();
    connect(m_tcpClientConnection, SIGNAL(readyRead()), this, SLOT(readHead()));
    connect(m_tcpClientConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    qDebug() << "AcceptConnection OK";
}


// Get local IP address
QString Client::getLocalIP()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address() &&
            (ipAddressesList.at(i).toString().indexOf("168") != (-1))) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}


// Error display
void Client::displayError(QAbstractSocket::SocketError)
{
    qCWarning(CLIENT()) << CLIENT().categoryName() << ":" << m_tcpClient.errorString();
}


void Client::readHead()
{
    QDataStream in(m_tcpClientConnection);
    in.setVersion(QDataStream::Qt_4_6);

    qDebug() << "Ready read...";
    qint64 head;
    qDebug() << "Reading head...";

    in >> head;
    if (head == 1)
    {
        receiveCommand();
    }
    if (head == 2)
    {
        receivePlanHash();
    }
}


// Variables initialization
void Client::varInit()
{
    m_hashX.clear();
    m_hashY.clear();
    m_hashZ.clear();
    m_spot3D.clear();
    m_spotOrder.clear();
    m_parameter.volt = 0;
    m_parameter.totalTime = 0;
    m_parameter.period = 0;
    m_parameter.dutyCycle = 0;
    m_parameter.coolingTime = 0;
    m_outBlock.resize(0);
}


// Receive treatment plan from another computer
void Client::receivePlanHash()
{
    varInit();

    QDataStream in(m_tcpClientConnection);
    in.setVersion(QDataStream::Qt_4_6);

    qDebug() << "Receiving plan...";
    QString sendInfo;

    in >> m_totalBytes
            >> m_hashX
            >> m_hashY
            >> m_hashZ
            >> m_spotOrder
            >> m_parameter.volt
            >> m_parameter.totalTime
            >> m_parameter.period
            >> m_parameter.dutyCycle
            >> m_parameter.coolingTime
            >> sendInfo;

    qDebug() << "m_totalBytes:" << m_totalBytes;
    qDebug() << "m_hashX:" << m_hashX;
    qDebug() << "m_hashY:" << m_hashY;
    qDebug() << "m_hashZ:" << m_hashZ;
    qDebug() << "m_spotOrder:" << m_spotOrder;
    qDebug() << "Volt:" << m_parameter.volt << "Total time:" << m_parameter.totalTime << "Period:" << m_parameter.period
             << "Duty cycle:" << m_parameter.dutyCycle << "Cooling time:" << m_parameter.coolingTime;
    qDebug() << "sendInfo:" << sendInfo;

    qDebug() << "Receive plan finished.";

    QDataStream out(&m_outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    qDebug() << "Write back...";

    out << sendInfo;

    // If need to print bytesWritten information, un-comment the line below
//    connect(m_tcpClientConnection, SIGNAL(bytesWritten(qint64)), this, SLOT(bytes(qint64)));
    m_tcpClientConnection->write(m_outBlock);

    m_tcpClientConnection->close();

    qDebug() << sendInfo;

    qDebug() << "Send back finished.";
    qDebug() << "-------------------";

    convertSpot();

    qCDebug(CLIENT()) << CLIENT().categoryName() << ":" << "RECEIVE TREATMENT PLAN SUCCEEDED.";
    qDebug() << "*******************";
}


// Convert the spots information to standard form
void Client::convertSpot()
{
    QHash<float, QList<float> >::iterator i;
    for (i = m_hashX.begin(); i != m_hashX.end(); ++i)
    {
        float currentKey = i.key();
        QList<float> currentListX = i.value();
        QList<float> currentListY = m_hashY[currentKey];
        QList<float> currentListZ = m_hashZ[currentKey];
        int currentlistSize = currentListX.size();
        for (int x = 0; x < currentlistSize; x++)
        {
            Spot3DCoordinate currentSpot;
            currentSpot.x = currentListX.at(x);
            currentSpot.y = currentListY.at(x);
            currentSpot.z = currentListZ.at(x);
            m_spot3D[currentKey].append(currentSpot);
        }
    }

    // Print to check
    QHash<float, QList<Spot3DCoordinate> >::iterator j;
    for (j = m_spot3D.begin(); j != m_spot3D.end(); ++j)
    {
        QList<Spot3DCoordinate> currentList = j.value();
        qDebug() << j.key() << ":"
                 << "First spot:" << "(" << currentList.at(0).x << ","
                 << currentList.at(0).y << ","
                 << currentList.at(0).z << ")";
        qDebug() << "Size:" << currentList.size();
    }
}


// Receive command: 1 start, 2 stop, 3 pause, 4 resume
void Client::receiveCommand()
{
    QDataStream in(m_tcpClientConnection);
    in.setVersion(QDataStream::Qt_4_6);

    qDebug() << "Receiving command...";

    in >> m_command;

    qDebug() << m_command;

    switch (m_command) {
    case 1:
        emit commandStart(); qDebug() << "Start";
        qCDebug(CLIENT()) << CLIENT().categoryName() << ":" << "RECEIVED COMMAND START.";
        break;
    case 2:
        emit commandStop(); qDebug() << "Stop";
        qCDebug(CLIENT()) << CLIENT().categoryName() << ":" << "RECEIVED COMMAND STOP.";
        break;
    case 3:
        emit commandPause(); qDebug() << "Pause";
        qCDebug(CLIENT()) << CLIENT().categoryName() << ":" << "RECEIVED COMMAND PAUSE.";
        break;
    case 4:
        emit commandResume(); qDebug() << "Resume";
        qCDebug(CLIENT()) << CLIENT().categoryName() << ":" << "RECEIVED COMMAND RESUME.";
        break;
    default:
        break;
    }

    m_tcpClientConnection->close();
    qDebug() << "Receive command finished.";
    qDebug() << endl << "*******************";
}


// Check whether the send-back data is right, not necessary
void Client::bytes(qint64 byteswrite)
{
    qDebug() << "Bytes Written:" << byteswrite;
}


QHash<float, QList<Spot3DCoordinate> > Client::getCoordinate()
{
    return m_spot3D;
}

QHash<float, QList<int> > Client::getSpotOrder()
{
    return m_spotOrder;
}

SpotSonicationParam Client::getParameter()
{
    return m_parameter;
}
