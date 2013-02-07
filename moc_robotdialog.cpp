/****************************************************************************
** Meta object code from reading C++ file 'robotdialog.h'
**
** Created: Thu Mar 27 13:26:20 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "robotdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RobotDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      23,   12,   12,   12, 0x0a,
      34,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RobotDialog[] = {
    "RobotDialog\0\0mapOpen()\0nextStep()\0"
    "paintEvent(QPaintEvent*)\0"
};

const QMetaObject RobotDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RobotDialog,
      qt_meta_data_RobotDialog, 0 }
};

const QMetaObject *RobotDialog::metaObject() const
{
    return &staticMetaObject;
}

void *RobotDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RobotDialog))
	return static_cast<void*>(const_cast< RobotDialog*>(this));
    if (!strcmp(_clname, "Ui::RobotDialog"))
	return static_cast< Ui::RobotDialog*>(const_cast< RobotDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RobotDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mapOpen(); break;
        case 1: nextStep(); break;
        case 2: paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}
