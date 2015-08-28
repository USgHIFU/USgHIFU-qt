#ifndef CLIENT_GLOBAL_H
#define CLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CLIENT_LIBRARY)
#  define CLIENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLIENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLIENT_GLOBAL_H
