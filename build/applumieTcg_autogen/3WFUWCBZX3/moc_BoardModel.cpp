/****************************************************************************
** Meta object code from reading C++ file 'BoardModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Models/BoardModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BoardModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10BoardModelE_t {};
} // unnamed namespace

template <> constexpr inline auto BoardModel::qt_create_metaobjectdata<qt_meta_tag_ZN10BoardModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BoardModel",
        "matchIdChanged",
        "",
        "roundChanged",
        "stageChanged",
        "weatherChanged",
        "selfPlayerChanged",
        "opponentPlayerChanged",
        "turnChanged",
        "matchId",
        "round",
        "stage",
        "currentWeather",
        "weatherName",
        "weatherDescription",
        "weatherIcon",
        "weatherRemainingRounds",
        "weatherSequence",
        "selfPlayer",
        "PlayerModel*",
        "opponentPlayer",
        "isMyTurn"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'matchIdChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'roundChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stageChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'weatherChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selfPlayerChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'opponentPlayerChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'turnChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'matchId'
        QtMocHelpers::PropertyData<QString>(9, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'round'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'stage'
        QtMocHelpers::PropertyData<QString>(11, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'currentWeather'
        QtMocHelpers::PropertyData<QString>(12, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherName'
        QtMocHelpers::PropertyData<QString>(13, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherDescription'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherIcon'
        QtMocHelpers::PropertyData<QString>(15, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherRemainingRounds'
        QtMocHelpers::PropertyData<int>(16, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'weatherSequence'
        QtMocHelpers::PropertyData<QStringList>(17, QMetaType::QStringList, QMC::DefaultPropertyFlags, 3),
        // property 'selfPlayer'
        QtMocHelpers::PropertyData<PlayerModel*>(18, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'opponentPlayer'
        QtMocHelpers::PropertyData<PlayerModel*>(20, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 5),
        // property 'isMyTurn'
        QtMocHelpers::PropertyData<bool>(21, QMetaType::Bool, QMC::DefaultPropertyFlags, 6),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BoardModel, qt_meta_tag_ZN10BoardModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BoardModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BoardModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BoardModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10BoardModelE_t>.metaTypes,
    nullptr
} };

void BoardModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BoardModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->matchIdChanged(); break;
        case 1: _t->roundChanged(); break;
        case 2: _t->stageChanged(); break;
        case 3: _t->weatherChanged(); break;
        case 4: _t->selfPlayerChanged(); break;
        case 5: _t->opponentPlayerChanged(); break;
        case 6: _t->turnChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::matchIdChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::roundChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::stageChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::weatherChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::selfPlayerChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::opponentPlayerChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BoardModel::*)()>(_a, &BoardModel::turnChanged, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
        case 9:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PlayerModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->matchId(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->round(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->stageText(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->currentWeatherText(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->weatherName(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->weatherDescription(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->weatherIcon(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->weatherRemainingRounds(); break;
        case 8: *reinterpret_cast<QStringList*>(_v) = _t->weatherSequence(); break;
        case 9: *reinterpret_cast<PlayerModel**>(_v) = _t->selfPlayer(); break;
        case 10: *reinterpret_cast<PlayerModel**>(_v) = _t->opponentPlayer(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->isMyTurn(); break;
        default: break;
        }
    }
}

const QMetaObject *BoardModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BoardModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BoardModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BoardModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void BoardModel::matchIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BoardModel::roundChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BoardModel::stageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BoardModel::weatherChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BoardModel::selfPlayerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BoardModel::opponentPlayerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BoardModel::turnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
