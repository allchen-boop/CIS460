/****************************************************************************
** Meta object code from reading C++ file 'mygl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../hw07/assignment_package/src/mygl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGL_t {
    QByteArrayData data[20];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGL_t qt_meta_stringdata_MyGL = {
    {
QT_MOC_LITERAL(0, 0, 4), // "MyGL"
QT_MOC_LITERAL(1, 5, 12), // "sig_sendMesh"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "Mesh*"
QT_MOC_LITERAL(4, 25, 16), // "sig_sendSkeleton"
QT_MOC_LITERAL(5, 42, 9), // "Skeleton*"
QT_MOC_LITERAL(6, 52, 6), // "slot_x"
QT_MOC_LITERAL(7, 59, 6), // "slot_y"
QT_MOC_LITERAL(8, 66, 6), // "slot_z"
QT_MOC_LITERAL(9, 73, 8), // "slot_red"
QT_MOC_LITERAL(10, 82, 10), // "slot_green"
QT_MOC_LITERAL(11, 93, 9), // "slot_blue"
QT_MOC_LITERAL(12, 103, 11), // "slot_select"
QT_MOC_LITERAL(13, 115, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 132, 12), // "slot_addVert"
QT_MOC_LITERAL(15, 145, 16), // "slot_triangulate"
QT_MOC_LITERAL(16, 162, 14), // "slot_subdivide"
QT_MOC_LITERAL(17, 177, 14), // "slot_importOBJ"
QT_MOC_LITERAL(18, 192, 13), // "slot_loadJSON"
QT_MOC_LITERAL(19, 206, 13) // "slot_skinMesh"

    },
    "MyGL\0sig_sendMesh\0\0Mesh*\0sig_sendSkeleton\0"
    "Skeleton*\0slot_x\0slot_y\0slot_z\0slot_red\0"
    "slot_green\0slot_blue\0slot_select\0"
    "QListWidgetItem*\0slot_addVert\0"
    "slot_triangulate\0slot_subdivide\0"
    "slot_importOBJ\0slot_loadJSON\0slot_skinMesh"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGL[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   95,    2, 0x0a /* Public */,
       7,    1,   98,    2, 0x0a /* Public */,
       8,    1,  101,    2, 0x0a /* Public */,
       9,    1,  104,    2, 0x0a /* Public */,
      10,    1,  107,    2, 0x0a /* Public */,
      11,    1,  110,    2, 0x0a /* Public */,
      12,    1,  113,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    0,  120,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_sendMesh((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 1: _t->sig_sendSkeleton((*reinterpret_cast< Skeleton*(*)>(_a[1]))); break;
        case 2: _t->slot_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->slot_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->slot_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->slot_red((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->slot_green((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->slot_blue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->slot_select((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->slot_addVert(); break;
        case 10: _t->slot_triangulate(); break;
        case 11: _t->slot_subdivide(); break;
        case 12: _t->slot_importOBJ(); break;
        case 13: _t->slot_loadJSON(); break;
        case 14: _t->slot_skinMesh(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendMesh)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGL::*)(Skeleton * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendSkeleton)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyGL::staticMetaObject = { {
    &OpenGLContext::staticMetaObject,
    qt_meta_stringdata_MyGL.data,
    qt_meta_data_MyGL,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGL.stringdata0))
        return static_cast<void*>(this);
    return OpenGLContext::qt_metacast(_clname);
}

int MyGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OpenGLContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MyGL::sig_sendMesh(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyGL::sig_sendSkeleton(Skeleton * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
