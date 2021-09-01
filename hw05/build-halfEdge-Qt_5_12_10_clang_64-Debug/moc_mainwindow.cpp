/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../hw07/assignment_package/src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 34), // "on_actionCamera_Controls_trig..."
QT_MOC_LITERAL(4, 71, 16), // "slot_receiveMesh"
QT_MOC_LITERAL(5, 88, 5), // "Mesh*"
QT_MOC_LITERAL(6, 94, 20), // "slot_receiveSkeleton"
QT_MOC_LITERAL(7, 115, 9), // "Skeleton*"
QT_MOC_LITERAL(8, 125, 16), // "slot_selectJoint"
QT_MOC_LITERAL(9, 142, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(10, 159, 14), // "slot_jointPosX"
QT_MOC_LITERAL(11, 174, 14), // "slot_jointPosY"
QT_MOC_LITERAL(12, 189, 14), // "slot_jointPosZ"
QT_MOC_LITERAL(13, 204, 17), // "slot_jointRotXPos"
QT_MOC_LITERAL(14, 222, 17), // "slot_jointRotXNeg"
QT_MOC_LITERAL(15, 240, 17), // "slot_jointRotYPos"
QT_MOC_LITERAL(16, 258, 17), // "slot_jointRotYNeg"
QT_MOC_LITERAL(17, 276, 17), // "slot_jointRotZPos"
QT_MOC_LITERAL(18, 294, 17) // "slot_jointRotZNeg"

    },
    "MainWindow\0on_actionQuit_triggered\0\0"
    "on_actionCamera_Controls_triggered\0"
    "slot_receiveMesh\0Mesh*\0slot_receiveSkeleton\0"
    "Skeleton*\0slot_selectJoint\0QTreeWidgetItem*\0"
    "slot_jointPosX\0slot_jointPosY\0"
    "slot_jointPosZ\0slot_jointRotXPos\0"
    "slot_jointRotXNeg\0slot_jointRotYPos\0"
    "slot_jointRotYNeg\0slot_jointRotZPos\0"
    "slot_jointRotZNeg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x0a /* Public */,
       6,    1,   89,    2, 0x0a /* Public */,
       8,    2,   92,    2, 0x0a /* Public */,
      10,    1,   97,    2, 0x0a /* Public */,
      11,    1,  100,    2, 0x0a /* Public */,
      12,    1,  103,    2, 0x0a /* Public */,
      13,    0,  106,    2, 0x0a /* Public */,
      14,    0,  107,    2, 0x0a /* Public */,
      15,    0,  108,    2, 0x0a /* Public */,
      16,    0,  109,    2, 0x0a /* Public */,
      17,    0,  110,    2, 0x0a /* Public */,
      18,    0,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionQuit_triggered(); break;
        case 1: _t->on_actionCamera_Controls_triggered(); break;
        case 2: _t->slot_receiveMesh((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 3: _t->slot_receiveSkeleton((*reinterpret_cast< Skeleton*(*)>(_a[1]))); break;
        case 4: _t->slot_selectJoint((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->slot_jointPosX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->slot_jointPosY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->slot_jointPosZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->slot_jointRotXPos(); break;
        case 9: _t->slot_jointRotXNeg(); break;
        case 10: _t->slot_jointRotYPos(); break;
        case 11: _t->slot_jointRotYNeg(); break;
        case 12: _t->slot_jointRotZPos(); break;
        case 13: _t->slot_jointRotZNeg(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
