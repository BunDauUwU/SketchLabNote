/****************************************************************************
** Meta object code from reading C++ file 'GameManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Managers/GameManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11GameManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto GameManager::qt_create_metaobjectdata<qt_meta_tag_ZN11GameManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GameManager",
        "matchIdChanged",
        "",
        "playerIndexChanged",
        "opponentNameChanged",
        "stageChanged",
        "gameError",
        "message",
        "gameSnapshotReceived",
        "QJsonObject",
        "snapshot",
        "gameEventsReceived",
        "QJsonArray",
        "events",
        "gameEnded",
        "reason",
        "handleServerMessage",
        "setMatchInfo",
        "matchId",
        "playerIndex",
        "opponentName",
        "chooseActiveCharacter",
        "characterIndex",
        "endRound",
        "useSkill",
        "skillIndex",
        "elementPointCost",
        "QVariantMap",
        "target",
        "playCard",
        "handIndex",
        "stage",
        "board",
        "BoardModel*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'matchIdChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playerIndexChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'opponentNameChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stageChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gameError'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'gameSnapshotReceived'
        QtMocHelpers::SignalData<void(const QJsonObject &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'gameEventsReceived'
        QtMocHelpers::SignalData<void(const QJsonArray &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Signal 'gameEnded'
        QtMocHelpers::SignalData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'handleServerMessage'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 7 },
        }}),
        // Method 'setMatchInfo'
        QtMocHelpers::MethodData<void(const QString &, int, const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::Int, 19 }, { QMetaType::QString, 20 },
        }}),
        // Method 'chooseActiveCharacter'
        QtMocHelpers::MethodData<void(int)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 22 },
        }}),
        // Method 'endRound'
        QtMocHelpers::MethodData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'useSkill'
        QtMocHelpers::MethodData<void(int, int, const QVariantMap &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 25 }, { QMetaType::Int, 26 }, { 0x80000000 | 27, 28 },
        }}),
        // Method 'playCard'
        QtMocHelpers::MethodData<void(int, int, const QVariantMap &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 30 }, { QMetaType::Int, 26 }, { 0x80000000 | 27, 28 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'matchId'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'playerIndex'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'opponentName'
        QtMocHelpers::PropertyData<QString>(20, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'stage'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'board'
        QtMocHelpers::PropertyData<BoardModel*>(32, 0x80000000 | 33, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<GameManager, qt_meta_tag_ZN11GameManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject GameManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11GameManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11GameManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11GameManagerE_t>.metaTypes,
    nullptr
} };

void GameManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->matchIdChanged(); break;
        case 1: _t->playerIndexChanged(); break;
        case 2: _t->opponentNameChanged(); break;
        case 3: _t->stageChanged(); break;
        case 4: _t->gameError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->gameSnapshotReceived((*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 6: _t->gameEventsReceived((*reinterpret_cast<std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 7: _t->gameEnded((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->handleServerMessage((*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 9: _t->setMatchInfo((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 10: _t->chooseActiveCharacter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->endRound(); break;
        case 12: _t->useSkill((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[3]))); break;
        case 13: _t->playCard((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)()>(_a, &GameManager::matchIdChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)()>(_a, &GameManager::playerIndexChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)()>(_a, &GameManager::opponentNameChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)()>(_a, &GameManager::stageChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)(const QString & )>(_a, &GameManager::gameError, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)(const QJsonObject & )>(_a, &GameManager::gameSnapshotReceived, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)(const QJsonArray & )>(_a, &GameManager::gameEventsReceived, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameManager::*)(const QString & )>(_a, &GameManager::gameEnded, 7))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BoardModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->matchId(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->playerIndex(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->opponentName(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->stageText(); break;
        case 4: *reinterpret_cast<BoardModel**>(_v) = _t->board(); break;
        default: break;
        }
    }
}

const QMetaObject *GameManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11GameManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GameManager::matchIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GameManager::playerIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GameManager::opponentNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GameManager::stageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GameManager::gameError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void GameManager::gameSnapshotReceived(const QJsonObject & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void GameManager::gameEventsReceived(const QJsonArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void GameManager::gameEnded(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
