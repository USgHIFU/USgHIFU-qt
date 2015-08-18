#ifndef PERFORMANCEMONITOR_H
#define PERFORMANCEMONITOR_H

class QTimer;

#include <QObject>
#include "windows.h"
#include "performancemonitor_global.h"

class PERFORMANCEMONITORSHARED_EXPORT PerformanceMonitor : public QObject
{
    Q_OBJECT
public:
    PerformanceMonitor(QObject* parent = 0);

    bool shutDownPC();

signals:
    memLoadUpdate(DWORD memLoad);
    memAvailPhysUpdate(DWORDLONG availPhys);

private slots:
    void updateMemStatus();

private:
    QTimer* timer;

    MEMORYSTATUSEX memStatus;

    DWORD getMemoryLoad();
    DWORDLONG getAvailPhys();



};

#endif // PERFORMANCEMONITOR_H
