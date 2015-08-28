/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[25];
    char stringdata[349];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 12), // "commandStart"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "commandStop"
QT_MOC_LITERAL(4, 33, 12), // "commandPause"
QT_MOC_LITERAL(5, 46, 13), // "commandResume"
QT_MOC_LITERAL(6, 60, 16), // "acceptConnection"
QT_MOC_LITERAL(7, 77, 12), // "displayError"
QT_MOC_LITERAL(8, 90, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 119, 11), // "socketError"
QT_MOC_LITERAL(10, 131, 10), // "getLocalIP"
QT_MOC_LITERAL(11, 142, 11), // "convertSpot"
QT_MOC_LITERAL(12, 154, 8), // "readHead"
QT_MOC_LITERAL(13, 163, 15), // "receivePlanHash"
QT_MOC_LITERAL(14, 179, 14), // "receiveCommand"
QT_MOC_LITERAL(15, 194, 5), // "bytes"
QT_MOC_LITERAL(16, 200, 10), // "byteswrite"
QT_MOC_LITERAL(17, 211, 7), // "varInit"
QT_MOC_LITERAL(18, 219, 6), // "listen"
QT_MOC_LITERAL(19, 226, 13), // "getCoordinate"
QT_MOC_LITERAL(20, 240, 37), // "QHash<float,QList<Spot3DCoord..."
QT_MOC_LITERAL(21, 278, 12), // "getSpotOrder"
QT_MOC_LITERAL(22, 291, 24), // "QHash<float,QList<int> >"
QT_MOC_LITERAL(23, 316, 12), // "getParameter"
QT_MOC_LITERAL(24, 329, 19) // "SpotSonicationParam"

    },
    "Client\0commandStart\0\0commandStop\0"
    "commandPause\0commandResume\0acceptConnection\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "socketError\0getLocalIP\0convertSpot\0"
    "readHead\0receivePlanHash\0receiveCommand\0"
    "bytes\0byteswrite\0varInit\0listen\0"
    "getCoordinate\0QHash<float,QList<Spot3DCoordinate> >\0"
    "getSpotOrder\0QHash<float,QList<int> >\0"
    "getParameter\0SpotSonicationParam"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x06 /* Public */,
       5,    0,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  103,    2, 0x08 /* Private */,
       7,    1,  104,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    1,  112,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x0a /* Public */,
      19,    0,  117,    2, 0x0a /* Public */,
      21,    0,  118,    2, 0x0a /* Public */,
      23,    0,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   16,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 20,
    0x80000000 | 22,
    0x80000000 | 24,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        switch (_id) {
        case 0: { int _r = _t->commandStart();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->commandStop();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->commandPause();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->commandResume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->acceptConnection(); break;
        case 5: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: { QString _r = _t->getLocalIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: _t->convertSpot(); break;
        case 8: _t->readHead(); break;
        case 9: _t->receivePlanHash(); break;
        case 10: _t->receiveCommand(); break;
        case 11: _t->bytes((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 12: _t->varInit(); break;
        case 13: _t->listen(); break;
        case 14: { QHash<float,QList<Spot3DCoordinate> > _r = _t->getCoordinate();
            if (_a[0]) *reinterpret_cast< QHash<float,QList<Spot3DCoordinate> >*>(_a[0]) = _r; }  break;
        case 15: { QHash<float,QList<int> > _r = _t->getSpotOrder();
            if (_a[0]) *reinterpret_cast< QHash<float,QList<int> >*>(_a[0]) = _r; }  break;
        case 16: { SpotSonicationParam _r = _t->getParameter();
            if (_a[0]) *reinterpret_cast< SpotSonicationParam*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::commandStart)) {
                *result = 0;
            }
        }
        {
            typedef int (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::commandStop)) {
                *result = 1;
            }
        }
        {
            typedef int (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::commandPause)) {
                *result = 2;
            }
        }
        {
            typedef int (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::commandResume)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata))
        return static_cast<void*>(const_cast< Client*>(this));
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
int Client::commandStart()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int Client::commandStop()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
int Client::commandPause()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
int Client::commandResume()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
