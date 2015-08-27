#ifndef PERFORMANCEMONITOR_GLOBAL_H
#define PERFORMANCEMONITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PERFORMANCEMONITOR_LIBRARY)
#  define PERFORMANCEMONITORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PERFORMANCEMONITORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PERFORMANCEMONITOR_GLOBAL_H