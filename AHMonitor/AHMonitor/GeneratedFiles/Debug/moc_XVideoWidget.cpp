/****************************************************************************
** Meta object code from reading C++ file 'XVideoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XVideoWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XVideoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLYuvWidget_t {
    QByteArrayData data[7];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLYuvWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLYuvWidget_t qt_meta_stringdata_GLYuvWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GLYuvWidget"
QT_MOC_LITERAL(1, 12, 11), // "slotShowYuv"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "uchar*"
QT_MOC_LITERAL(4, 32, 3), // "ptr"
QT_MOC_LITERAL(5, 36, 5), // "width"
QT_MOC_LITERAL(6, 42, 6) // "height"

    },
    "GLYuvWidget\0slotShowYuv\0\0uchar*\0ptr\0"
    "width\0height"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLYuvWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, QMetaType::UInt,    4,    5,    6,

       0        // eod
};

void GLYuvWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLYuvWidget *_t = static_cast<GLYuvWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotShowYuv((*reinterpret_cast< uchar*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject GLYuvWidget::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_GLYuvWidget.data,
      qt_meta_data_GLYuvWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GLYuvWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLYuvWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLYuvWidget.stringdata0))
        return static_cast<void*>(const_cast< GLYuvWidget*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< GLYuvWidget*>(this));
    if (!strcmp(_clname, "IVideoCall"))
        return static_cast< IVideoCall*>(const_cast< GLYuvWidget*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int GLYuvWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
