#ifndef SERVER_GLOBAL_H
#define SERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SERVER_LIBRARY)
#  define SERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SERVER_GLOBAL_H
