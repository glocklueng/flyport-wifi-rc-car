/****************************************************************************
** Meta object code from reading C++ file 'fenetre.h'
**
** Created: Fri 11. May 14:35:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../rcwifi2/fenetre.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindows[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      27,   12,   12,   12, 0x0a,
      43,   12,   12,   12, 0x0a,
      59,   12,   12,   12, 0x0a,
      75,   12,   12,   12, 0x0a,
      92,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindows[] = {
    "MainWindows\0\0ouvrirSetup()\0envoyerGauche()\0"
    "envoyerDroite()\0envoyerNeutre()\0"
    "envoyerAvancer()\0envoyerStop()\0"
};

void MainWindows::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindows *_t = static_cast<MainWindows *>(_o);
        switch (_id) {
        case 0: _t->ouvrirSetup(); break;
        case 1: _t->envoyerGauche(); break;
        case 2: _t->envoyerDroite(); break;
        case 3: _t->envoyerNeutre(); break;
        case 4: _t->envoyerAvancer(); break;
        case 5: _t->envoyerStop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindows::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindows::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindows,
      qt_meta_data_MainWindows, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindows::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindows::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindows::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindows))
        return static_cast<void*>(const_cast< MainWindows*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindows::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
