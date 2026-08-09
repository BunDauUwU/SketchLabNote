/****************************************************************************
** Meta object code from reading C++ file 'MatchmakingManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Managers/MatchmakingManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MatchmakingManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18MatchmakingManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto MatchmakingManager::qt_create_metaobjectdata<qt_meta_tag_ZN18MatchmakingManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MatchmakingManager",
        "searchingChanged",
        "",
        "statusTextChanged",
        "matchFound",
        "matchId",
        "playerIndex",
        "opponentName",
        "matchmakingError",
        "message",
        "handleServerMessage",
        "QJsonObject",
        "startMatchmaking",
        "mode",
        "deckId",
        "cancelMatchmaking",
        "searching",
        "statusText"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'searchingChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusTextChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'matchFound'
        QtMocHelpers::SignalData<void(const QString &, int, const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 }, { QMetaType::Int, 6 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'matchmakingError'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'handleServerMessage'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 9 },
        }}),
        // Method 'startMatchmaking'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 14 },
        }}),
        // Method 'cancelMatchmaking'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'searching'
        QtMocHelpers::PropertyData<bool>(16, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'statusText'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MatchmakingManager, qt_meta_tag_ZN18MatchmakingManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MatchmakingManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18MatchmakingManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18MatchmakingManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18MatchmakingManagerE_t>.metaTypes,
    nullptr
} };

void MatchmakingManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MatchmakingManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->searchingChanged(); break;
        case 1: _t->statusTextChanged(); break;
        case 2: _t->matchFound((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->matchmakingError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->handleServerMessage((*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 5: _t->startMatchmaking((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->cancelMatchmaking(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MatchmakingManager::*)()>(_a, &MatchmakingManager::searchingChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MatchmakingManager::*)()>(_a, &MatchmakingManager::statusTextChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MatchmakingManager::*)(const QString & , int , const QString & )>(_a, &MatchmakingManager::matchFound, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MatchmakingManager::*)(const QString & )>(_a, &MatchmakingManager::matchmakingError, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isSearching(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->statusText(); break;
        default: break;
        }
    }
}

const QMetaObject *MatchmakingManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MatchmakingManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18MatchmakingManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MatchmakingManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MatchmakingManager::searchingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MatchmakingManager::statusTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MatchmakingManager::matchFound(const QString & _t1, int _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}

// SIGNAL 3
void MatchmakingManager::matchmakingError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
