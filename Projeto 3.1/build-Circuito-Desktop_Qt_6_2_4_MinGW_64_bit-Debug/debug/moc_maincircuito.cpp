/****************************************************************************
** Meta object code from reading C++ file 'maincircuito.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../circuito-interface_incompleto/maincircuito.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincircuito.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainCircuito_t {
    const uint offsetsAndSize[68];
    char stringdata0[499];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainCircuito_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainCircuito_t qt_meta_stringdata_MainCircuito = {
    {
QT_MOC_LITERAL(0, 12), // "MainCircuito"
QT_MOC_LITERAL(13, 18), // "signSetRangeInputs"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 6), // "minimo"
QT_MOC_LITERAL(40, 6), // "maximo"
QT_MOC_LITERAL(47, 19), // "signShowNewCircuito"
QT_MOC_LITERAL(67, 22), // "signShowModificarPorta"
QT_MOC_LITERAL(90, 6), // "IdPort"
QT_MOC_LITERAL(97, 8), // "TipoPort"
QT_MOC_LITERAL(106, 13), // "NumInputsPort"
QT_MOC_LITERAL(120, 8), // "IdInput0"
QT_MOC_LITERAL(129, 8), // "IdInput1"
QT_MOC_LITERAL(138, 8), // "IdInput2"
QT_MOC_LITERAL(147, 8), // "IdInput3"
QT_MOC_LITERAL(156, 22), // "signShowModificarSaida"
QT_MOC_LITERAL(179, 7), // "IdSaida"
QT_MOC_LITERAL(187, 13), // "IdOrigemSaida"
QT_MOC_LITERAL(201, 15), // "slotNewCircuito"
QT_MOC_LITERAL(217, 7), // "NInputs"
QT_MOC_LITERAL(225, 8), // "NOutputs"
QT_MOC_LITERAL(234, 7), // "NPortas"
QT_MOC_LITERAL(242, 18), // "slotModificarPorta"
QT_MOC_LITERAL(261, 18), // "slotModificarSaida"
QT_MOC_LITERAL(280, 7), // "idSaida"
QT_MOC_LITERAL(288, 13), // "idOrigemSaida"
QT_MOC_LITERAL(302, 23), // "on_actionSair_triggered"
QT_MOC_LITERAL(326, 23), // "on_actionNovo_triggered"
QT_MOC_LITERAL(350, 22), // "on_actionLer_triggered"
QT_MOC_LITERAL(373, 25), // "on_actionSalvar_triggered"
QT_MOC_LITERAL(399, 31), // "on_actionGerar_tabela_triggered"
QT_MOC_LITERAL(431, 24), // "on_tablePortas_activated"
QT_MOC_LITERAL(456, 11), // "QModelIndex"
QT_MOC_LITERAL(468, 5), // "index"
QT_MOC_LITERAL(474, 24) // "on_tableSaidas_activated"

    },
    "MainCircuito\0signSetRangeInputs\0\0"
    "minimo\0maximo\0signShowNewCircuito\0"
    "signShowModificarPorta\0IdPort\0TipoPort\0"
    "NumInputsPort\0IdInput0\0IdInput1\0"
    "IdInput2\0IdInput3\0signShowModificarSaida\0"
    "IdSaida\0IdOrigemSaida\0slotNewCircuito\0"
    "NInputs\0NOutputs\0NPortas\0slotModificarPorta\0"
    "slotModificarSaida\0idSaida\0idOrigemSaida\0"
    "on_actionSair_triggered\0on_actionNovo_triggered\0"
    "on_actionLer_triggered\0on_actionSalvar_triggered\0"
    "on_actionGerar_tabela_triggered\0"
    "on_tablePortas_activated\0QModelIndex\0"
    "index\0on_tableSaidas_activated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainCircuito[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   98,    2, 0x06,    1 /* Public */,
       5,    0,  103,    2, 0x06,    4 /* Public */,
       6,    7,  104,    2, 0x06,    5 /* Public */,
      14,    2,  119,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    3,  124,    2, 0x08,   16 /* Private */,
      21,    7,  131,    2, 0x08,   20 /* Private */,
      22,    2,  146,    2, 0x08,   28 /* Private */,
      25,    0,  151,    2, 0x08,   31 /* Private */,
      26,    0,  152,    2, 0x08,   32 /* Private */,
      27,    0,  153,    2, 0x08,   33 /* Private */,
      28,    0,  154,    2, 0x08,   34 /* Private */,
      29,    0,  155,    2, 0x08,   35 /* Private */,
      30,    1,  156,    2, 0x08,   36 /* Private */,
      33,    1,  159,    2, 0x08,   38 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,   16,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   18,   19,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void, 0x80000000 | 31,   32,

       0        // eod
};

void MainCircuito::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainCircuito *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signSetRangeInputs((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->signShowNewCircuito(); break;
        case 2: _t->signShowModificarPorta((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7]))); break;
        case 3: _t->signShowModificarSaida((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->slotNewCircuito((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->slotModificarPorta((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7]))); break;
        case 6: _t->slotModificarSaida((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->on_actionSair_triggered(); break;
        case 8: _t->on_actionNovo_triggered(); break;
        case 9: _t->on_actionLer_triggered(); break;
        case 10: _t->on_actionSalvar_triggered(); break;
        case 11: _t->on_actionGerar_tabela_triggered(); break;
        case 12: _t->on_tablePortas_activated((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 13: _t->on_tableSaidas_activated((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainCircuito::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainCircuito::signSetRangeInputs)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainCircuito::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainCircuito::signShowNewCircuito)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainCircuito::*)(int , QString , int , int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainCircuito::signShowModificarPorta)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainCircuito::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainCircuito::signShowModificarSaida)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MainCircuito::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainCircuito.offsetsAndSize,
    qt_meta_data_MainCircuito,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainCircuito_t
, QtPrivate::TypeAndForceComplete<MainCircuito, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainCircuito::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainCircuito::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainCircuito.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainCircuito::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainCircuito::signSetRangeInputs(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainCircuito::signShowNewCircuito()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainCircuito::signShowModificarPorta(int _t1, QString _t2, int _t3, int _t4, int _t5, int _t6, int _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainCircuito::signShowModificarSaida(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
