/****************************************************************************
** Meta object code from reading C++ file 'PlayerModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Models/PlayerModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlayerModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11PlayerModelE_t {};
} // unnamed namespace

template <> constexpr inline auto PlayerModel::qt_create_metaobjectdata<qt_meta_tag_ZN11PlayerModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlayerModel",
        "playerIdChanged",
        "",
        "nicknameChanged",
        "elementPointsChanged",
        "maxElementPointsChanged",
        "permanentEpBonusChanged",
        "handCardCountChanged",
        "deckCardCountChanged",
        "activeCharacterIndexChanged",
        "getCharacter",
        "CharacterModel*",
        "index",
        "playerId",
        "nickname",
        "elementPoints",
        "maxElementPoints",
        "permanentEpBonus",
        "handCardCount",
        "deckCardCount",
        "activeCharacterIndex"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'playerIdChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'nicknameChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'elementPointsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxElementPointsChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'permanentEpBonusChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'handCardCountChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'deckCardCountChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'activeCharacterIndexChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getCharacter'
        QtMocHelpers::MethodData<CharacterModel *(int) const>(10, 2, QMC::AccessPublic, 0x80000000 | 11, {{
            { QMetaType::Int, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'playerId'
        QtMocHelpers::PropertyData<QString>(13, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'nickname'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'elementPoints'
        QtMocHelpers::PropertyData<int>(15, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'maxElementPoints'
        QtMocHelpers::PropertyData<int>(16, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'permanentEpBonus'
        QtMocHelpers::PropertyData<int>(17, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'handCardCount'
        QtMocHelpers::PropertyData<int>(18, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'deckCardCount'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'activeCharacterIndex'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlayerModel, qt_meta_tag_ZN11PlayerModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlayerModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PlayerModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PlayerModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PlayerModelE_t>.metaTypes,
    nullptr
} };

void PlayerModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlayerModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->playerIdChanged(); break;
        case 1: _t->nicknameChanged(); break;
        case 2: _t->elementPointsChanged(); break;
        case 3: _t->maxElementPointsChanged(); break;
        case 4: _t->permanentEpBonusChanged(); break;
        case 5: _t->handCardCountChanged(); break;
        case 6: _t->deckCardCountChanged(); break;
        case 7: _t->activeCharacterIndexChanged(); break;
        case 8: { CharacterModel* _r = _t->getCharacter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<CharacterModel**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::playerIdChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::nicknameChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::elementPointsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::maxElementPointsChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::permanentEpBonusChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::handCardCountChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::deckCardCountChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerModel::*)()>(_a, &PlayerModel::activeCharacterIndexChanged, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->playerId(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->nickname(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->elementPoints(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->maxElementPoints(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->permanentEpBonus(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->handCardCount(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->deckCardCount(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->activeCharacterIndex(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPlayerId(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setNickname(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setElementPoints(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setMaxElementPoints(*reinterpret_cast<int*>(_v)); break;
        case 4: _t->setPermanentEpBonus(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setHandCardCount(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setDeckCardCount(*reinterpret_cast<int*>(_v)); break;
        case 7: _t->setActiveCharacterIndex(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *PlayerModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PlayerModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PlayerModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PlayerModel::playerIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlayerModel::nicknameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlayerModel::elementPointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PlayerModel::maxElementPointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PlayerModel::permanentEpBonusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlayerModel::handCardCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PlayerModel::deckCardCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PlayerModel::activeCharacterIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
