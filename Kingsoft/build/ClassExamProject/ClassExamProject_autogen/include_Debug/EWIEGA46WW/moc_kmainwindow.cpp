/****************************************************************************
** Meta object code from reading C++ file 'kmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "kmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KMainWindow_t qt_meta_stringdata_KMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "KMainWindow"
QT_MOC_LITERAL(1, 12, 22), // "handleSideWidthChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "width"
QT_MOC_LITERAL(4, 42, 23), // "handleShapeColorChanged"
QT_MOC_LITERAL(5, 66, 10), // "shapeColor"
QT_MOC_LITERAL(6, 77, 22), // "handleLineColorChanged"
QT_MOC_LITERAL(7, 100, 9), // "lineColor"
QT_MOC_LITERAL(8, 110, 9), // "editScale"
QT_MOC_LITERAL(9, 120, 5), // "scale"
QT_MOC_LITERAL(10, 126, 22), // "toSvgMainWindowNewFile"
QT_MOC_LITERAL(11, 149, 19), // "toSvgMainWindowSave"
QT_MOC_LITERAL(12, 169, 19), // "toSvgMainWindowOpen"
QT_MOC_LITERAL(13, 189, 24), // "toSvgMainWindowexportPNG"
QT_MOC_LITERAL(14, 214, 20) // "validateCanvasParams"

    },
    "KMainWindow\0handleSideWidthChanged\0\0"
    "width\0handleShapeColorChanged\0shapeColor\0"
    "handleLineColorChanged\0lineColor\0"
    "editScale\0scale\0toSvgMainWindowNewFile\0"
    "toSvgMainWindowSave\0toSvgMainWindowOpen\0"
    "toSvgMainWindowexportPNG\0validateCanvasParams"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,
      10,    0,   71,    2, 0x06 /* Public */,
      11,    0,   72,    2, 0x06 /* Public */,
      12,    0,   73,    2, 0x06 /* Public */,
      13,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void KMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handleSideWidthChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->handleShapeColorChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->handleLineColorChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->editScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->toSvgMainWindowNewFile(); break;
        case 5: _t->toSvgMainWindowSave(); break;
        case 6: _t->toSvgMainWindowOpen(); break;
        case 7: _t->toSvgMainWindowexportPNG(); break;
        case 8: _t->validateCanvasParams(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KMainWindow::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::handleSideWidthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::handleShapeColorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::handleLineColorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::editScale)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::toSvgMainWindowNewFile)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::toSvgMainWindowSave)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::toSvgMainWindowOpen)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (KMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KMainWindow::toSvgMainWindowexportPNG)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_KMainWindow.data,
    qt_meta_data_KMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int KMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void KMainWindow::handleSideWidthChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KMainWindow::handleShapeColorChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KMainWindow::handleLineColorChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KMainWindow::editScale(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void KMainWindow::toSvgMainWindowNewFile()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void KMainWindow::toSvgMainWindowSave()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void KMainWindow::toSvgMainWindowOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void KMainWindow::toSvgMainWindowexportPNG()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
