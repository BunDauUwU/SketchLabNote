/****************************************************************************
** Meta object code from reading C++ file 'CharacterModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Models/CharacterModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharacterModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14CharacterModelE_t {};
} // unnamed namespace

template <> constexpr inline auto CharacterModel::qt_create_metaobjectdata<qt_meta_tag_ZN14CharacterModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CharacterModel",
        "characterIdChanged",
        "",
        "hpChanged",
        "maxHpChanged",
        "energyChanged",
        "maxEnergyChanged",
        "elementChanged",
        "activeChanged",
        "defeatedChanged",
        "avatarPathChanged",
        "characterId",
        "hp",
        "maxHp",
        "energy",
        "maxEnergy",
        "element",
        "active",
        "defeated",
        "avatarPath"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'characterIdChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hpChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxHpChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'energyChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxEnergyChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'elementChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'activeChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'defeatedChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'avatarPathChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'characterId'
        QtMocHelpers::PropertyData<QString>(11, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'hp'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'maxHp'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'energy'
        QtMocHelpers::PropertyData<int>(14, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'maxEnergy'
        QtMocHelpers::PropertyData<int>(15, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'element'
        QtMocHelpers::PropertyData<QString>(16, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'active'
        QtMocHelpers::PropertyData<bool>(17, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'defeated'
        QtMocHelpers::PropertyData<bool>(18, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'avatarPath'
        QtMocHelpers::PropertyData<QString>(19, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CharacterModel, qt_meta_tag_ZN14CharacterModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CharacterModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CharacterModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CharacterModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14CharacterModelE_t>.metaTypes,
    nullptr
} };

void CharacterModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CharacterModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->characterIdChanged(); break;
        case 1: _t->hpChanged(); break;
        case 2: _t->maxHpChanged(); break;
        case 3: _t->energyChanged(); break;
        case 4: _t->maxEnergyChanged(); break;
        case 5: _t->elementChanged(); break;
        case 6: _t->activeChanged(); break;
        case 7: _t->defeatedChanged(); break;
        case 8: _t->avatarPathChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::characterIdChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::hpChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::maxHpChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::energyChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::maxEnergyChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::elementChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::activeChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::defeatedChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (CharacterModel::*)()>(_a, &CharacterModel::avatarPathChanged, 8))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->characterId(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->hp(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->maxHp(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->energy(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->maxEnergy(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->elementText(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->isActive(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->isDefeated(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->avatarPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCharacterId(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setHp(*reinterpret_cast<int*>(_v)); break;
        case 2: _t->setMaxHp(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setEnergy(*reinterpret_cast<int*>(_v)); break;
        case 4: _t->setMaxEnergy(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setActive(*reinterpret_cast<bool*>(_v)); break;
        case 7: _t->setDefeated(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *CharacterModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CharacterModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CharacterModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CharacterModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CharacterModel::characterIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CharacterModel::hpChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CharacterModel::maxHpChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CharacterModel::energyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CharacterModel::maxEnergyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CharacterModel::elementChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CharacterModel::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CharacterModel::defeatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void CharacterModel::avatarPathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
