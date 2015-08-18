#include "performancemonitor.h"
#include <QTimer>

PerformanceMonitor::PerformanceMonitor(QObject *parent) : QObject(parent)
{
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx(&memStatus);

    timer = new QTimer(this);
    timer->setInterval(5000);

    connect(timer,SIGNAL(timeout()),SLOT(updateMemStatus()));

    timer->start();
}

bool PerformanceMonitor::shutDownPC()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
    {
//        qDebug() << "Cannot find the current process.";
        return false;
    }

    LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS)
    {
//        qDebug() << "Cannot get the privilages.";
        return false;
    }

    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,0))
    {
//        qDebug() << "Cannot shut down the computer.";
        return false;
     }
     else
     {
//        qDebug() << "Shutting down the computer.";
        return true;
     }
}

DWORD PerformanceMonitor::getMemoryLoad()
{
    return memStatus.dwMemoryLoad;
}

DWORDLONG PerformanceMonitor::getAvailPhys()
{
    return memStatus.ullAvailPhys;
}

void PerformanceMonitor::updateMemStatus()
{
    emit memLoadUpdate(getMemoryLoad());
    emit memAvailPhysUpdate(getAvailPhys());
}
