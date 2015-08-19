#ifndef PERFORMANCEMONITOR_H
#define PERFORMANCEMONITOR_H

class QTimer;

#include <QObject>
#include <QLoggingCategory>
#include "windows.h"
#include "performancemonitor_global.h"

Q_DECLARE_LOGGING_CATEGORY(MEMORY_MONITOR)
Q_DECLARE_LOGGING_CATEGORY(SHUT_DOWN_PC)

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

    enum ShutDownAction
    {
        GetProcessToken,
        GetTokenPrivilage,
        ShutDown
    };

    enum MemoryMonitorAction
    {
        GetMemoryLoad,
        GetAvailPhys
    };

    MEMORYSTATUSEX memStatus;

    DWORD getMemoryLoad();
    DWORDLONG getAvailPhys();
};

#endif // PERFORMANCEMONITOR_H
