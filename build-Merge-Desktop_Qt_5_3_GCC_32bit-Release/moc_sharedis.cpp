/****************************************************************************
** Meta object code from reading C++ file 'sharedis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Merge/sharedis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sharedis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_shareDis_t {
    QByteArrayData data[6];
    char stringdata[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_shareDis_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_shareDis_t qt_meta_stringdata_shareDis = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 6),
QT_MOC_LITERAL(2, 16, 0),
QT_MOC_LITERAL(3, 17, 11),
QT_MOC_LITERAL(4, 29, 16),
QT_MOC_LITERAL(5, 46, 9)
    },
    "shareDis\0goback\0\0validateBut\0"
    "checkForValidity\0countDown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_shareDis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       4,    0,   38,    2, 0x08 /* Private */,
       5,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void shareDis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        shareDis *_t = static_cast<shareDis *>(_o);
        switch (_id) {
        case 0: _t->goback(); break;
        case 1: _t->validateBut((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->checkForValidity(); break;
        case 3: _t->countDown(); break;
        default: ;
        }
    }
}

const QMetaObject shareDis::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_shareDis.data,
      qt_meta_data_shareDis,  qt_static_metacall, 0, 0}
};


const QMetaObject *shareDis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *shareDis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_shareDis.stringdata))
        return static_cast<void*>(const_cast< shareDis*>(this));
    return QDialog::qt_metacast(_clname);
}

int shareDis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
