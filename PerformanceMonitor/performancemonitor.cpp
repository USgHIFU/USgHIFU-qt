#include "performancemonitor.h"
#include <QTimer>

Q_LOGGING_CATEGORY(MEMORY_MONITOR,"MEMORY MONITOR")
Q_LOGGING_CATEGORY(SHUT_DOWN_PC,"SHUT DOWN PC")

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
        qCWarning(SHUT_DOWN_PC()) << SHUT_DOWN_PC().categoryName()
                                  << "Action #" << GetProcessToken
                                  << "Result: cannot find the current process.";
        return false;
    }else
    {
        qCDebug(SHUT_DOWN_PC()) << SHUT_DOWN_PC().categoryName()
                                << "Action #" << GetProcessToken
                                << "Result: find the current process.";
    }

    LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS)
    {
        qCWarning(SHUT_DOWN_PC()) << SHUT_DOWN_PC().categoryName()
                                  << "Action #" << GetTokenPrivilage
                                  << "Result: cannot get the privilages.";
        return false;
    }else
    {
        qCDebug(SHUT_DOWN_PC()) << SHUT_DOWN_PC().categoryName()
                                << "Action #" << GetTokenPrivilage
                                << "Result: get the privilages.";
    }

    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,0))
    {
        qCWarning(SHUT_DOWN_PC()) << SHUT_DOWN_PC().categoryName()
                                  << "Action #" << ShutDown
                                  << "Result: cannot shut down the computer.";
        return false;
     }
     else
     {
        qCDebug(SHUT_DOWN_PC()) << SHUT_DOWN_PC().categoryName()
                                << "Action #" << ShutDown
                                << "Result: Shut down the computer successfully.";
        return true;
     }
}

DWORD PerformanceMonitor::getMemoryLoad()
{
    qCDebug(MEMORY_MONITOR()) << MEMORY_MONITOR().categoryName()
                              << "Action #" << GetMemoryLoad
                              << "Result: get the memory load successfully.";
    return memStatus.dwMemoryLoad;
}

DWORDLONG PerformanceMonitor::getAvailPhys()
{
    qCDebug(MEMORY_MONITOR()) << MEMORY_MONITOR().categoryName()
                              << "Action #" << GetAvailPhys
                              << "Result: get the available physical memory successfully.";
    return memStatus.ullAvailPhys;
}

void PerformanceMonitor::updateMemStatus()
{
    emit memLoadUpdate(getMemoryLoad());
    emit memAvailPhysUpdate(getAvailPhys());
}
