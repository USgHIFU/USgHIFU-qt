#ifndef DOCONTROLLER_H
#define DOCONTROLLER_H

#include "docontroller_global.h"
#include <QObject>
#include <QString>
#include "inc/bdaqctrl.h"
#include "constant.h"
#include "variable.h"

using namespace Automation::BDaq;

class DOCONTROLLERSHARED_EXPORT DOController : public QObject
{
    Q_OBJECT

public:
    DOController(QObject *parent = 0);
    ~DOController();
    void sendPhase(int channel, quint8 phase);
    void loadPhase();
    void enableDO();
    void disableDO();
    void writeData(int port, quint8 state);

signals:
    void errorOccurred(QString error);

private:
    InstantDoCtrl *m_instantDOCtrl;
    QString m_deviceName;
    void selectDevice(QString deviceName);
    void checkError(ErrorCode errorCode);
};

#endif // DOCONTROLLER_H
