#ifndef CONSOLEPLAN_GLOBAL_H
#define CONSOLEPLAN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONSOLEPLAN_LIBRARY)
#  define CONSOLEPLANSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONSOLEPLANSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONSOLEPLAN_GLOBAL_H
