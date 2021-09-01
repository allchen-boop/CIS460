/****************************************************************************
** Meta object code from reading C++ file 'mygl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../assignment_package/src/mygl.h"
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
    QByteArrayData data[28];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGL_t qt_meta_stringdata_MyGL = {
    {
QT_MOC_LITERAL(0, 0, 4), // "MyGL"
QT_MOC_LITERAL(1, 5, 18), // "sig_sendVertexData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "Mesh*"
QT_MOC_LITERAL(4, 31, 4), // "mesh"
QT_MOC_LITERAL(5, 36, 16), // "sig_sendFaceData"
QT_MOC_LITERAL(6, 53, 20), // "sig_sendHalfEdgeData"
QT_MOC_LITERAL(7, 74, 13), // "slot_vertPosX"
QT_MOC_LITERAL(8, 88, 1), // "x"
QT_MOC_LITERAL(9, 90, 13), // "slot_vertPosY"
QT_MOC_LITERAL(10, 104, 1), // "y"
QT_MOC_LITERAL(11, 106, 13), // "slot_vertPosZ"
QT_MOC_LITERAL(12, 120, 1), // "z"
QT_MOC_LITERAL(13, 122, 12), // "slot_faceRed"
QT_MOC_LITERAL(14, 135, 3), // "red"
QT_MOC_LITERAL(15, 139, 14), // "slot_faceGreen"
QT_MOC_LITERAL(16, 154, 5), // "green"
QT_MOC_LITERAL(17, 160, 13), // "slot_faceBlue"
QT_MOC_LITERAL(18, 174, 4), // "blue"
QT_MOC_LITERAL(19, 179, 14), // "slot_splitEdge"
QT_MOC_LITERAL(20, 194, 16), // "slot_triangulate"
QT_MOC_LITERAL(21, 211, 22), // "slot_setSelectedVertex"
QT_MOC_LITERAL(22, 234, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(23, 251, 1), // "v"
QT_MOC_LITERAL(24, 253, 20), // "slot_setSelectedFace"
QT_MOC_LITERAL(25, 274, 1), // "f"
QT_MOC_LITERAL(26, 276, 24), // "slot_setSelectedHalfEdge"
QT_MOC_LITERAL(27, 301, 2) // "he"

    },
    "MyGL\0sig_sendVertexData\0\0Mesh*\0mesh\0"
    "sig_sendFaceData\0sig_sendHalfEdgeData\0"
    "slot_vertPosX\0x\0slot_vertPosY\0y\0"
    "slot_vertPosZ\0z\0slot_faceRed\0red\0"
    "slot_faceGreen\0green\0slot_faceBlue\0"
    "blue\0slot_splitEdge\0slot_triangulate\0"
    "slot_setSelectedVertex\0QListWidgetItem*\0"
    "v\0slot_setSelectedFace\0f\0"
    "slot_setSelectedHalfEdge\0he"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGL[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       6,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   93,    2, 0x0a /* Public */,
       9,    1,   96,    2, 0x0a /* Public */,
      11,    1,   99,    2, 0x0a /* Public */,
      13,    1,  102,    2, 0x0a /* Public */,
      15,    1,  105,    2, 0x0a /* Public */,
      17,    1,  108,    2, 0x0a /* Public */,
      19,    0,  111,    2, 0x0a /* Public */,
      20,    0,  112,    2, 0x0a /* Public */,
      21,    1,  113,    2, 0x0a /* Public */,
      24,    1,  116,    2, 0x0a /* Public */,
      26,    1,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   25,
    QMetaType::Void, 0x80000000 | 22,   27,

       0        // eod
};

void MyGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_sendVertexData((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 1: _t->sig_sendFaceData((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 2: _t->sig_sendHalfEdgeData((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 3: _t->slot_vertPosX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->slot_vertPosY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->slot_vertPosZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->slot_faceRed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->slot_faceGreen((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->slot_faceBlue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->slot_splitEdge(); break;
        case 10: _t->slot_triangulate(); break;
        case 11: _t->slot_setSelectedVertex((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 12: _t->slot_setSelectedFace((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->slot_setSelectedHalfEdge((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendVertexData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendFaceData)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendHalfEdgeData)) {
                *result = 2;
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

// SIGNAL 0
void MyGL::sig_sendVertexData(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyGL::sig_sendFaceData(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyGL::sig_sendHalfEdgeData(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
