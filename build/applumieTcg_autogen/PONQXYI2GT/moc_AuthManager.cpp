/****************************************************************************
** Meta object code from reading C++ file 'AuthManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Managers/AuthManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AuthManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11AuthManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto AuthManager::qt_create_metaobjectdata<qt_meta_tag_ZN11AuthManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AuthManager",
        "usernameChanged",
        "",
        "authStateChanged",
        "statusMessageChanged",
        "loginSuccess",
        "username",
        "loginFailed",
        "error",
        "registerSuccess",
        "registerFailed",
        "handleServerMessage",
        "QJsonObject",
        "message",
        "login",
        "password",
        "registerUser",
        "logout",
        "nickname",
        "isAuthenticated",
        "statusMessage"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'usernameChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'authStateChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusMessageChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loginSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'loginFailed'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'registerSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'registerFailed'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Slot 'handleServerMessage'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Method 'login'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 15 },
        }}),
        // Method 'registerUser'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 15 },
        }}),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'username'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'nickname'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'isAuthenticated'
        QtMocHelpers::PropertyData<bool>(19, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'statusMessage'
        QtMocHelpers::PropertyData<QString>(20, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AuthManager, qt_meta_tag_ZN11AuthManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AuthManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AuthManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AuthManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11AuthManagerE_t>.metaTypes,
    nullptr
} };

void AuthManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AuthManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->usernameChanged(); break;
        case 1: _t->authStateChanged(); break;
        case 2: _t->statusMessageChanged(); break;
        case 3: _t->loginSuccess((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->loginFailed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->registerSuccess((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->registerFailed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->handleServerMessage((*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 8: { bool _r = _t->login((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->registerUser((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->logout(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)()>(_a, &AuthManager::usernameChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)()>(_a, &AuthManager::authStateChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)()>(_a, &AuthManager::statusMessageChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)(const QString & )>(_a, &AuthManager::loginSuccess, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)(const QString & )>(_a, &AuthManager::loginFailed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)(const QString & )>(_a, &AuthManager::registerSuccess, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthManager::*)(const QString & )>(_a, &AuthManager::registerFailed, 6))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->username(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->username(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isAuthenticated(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->statusMessage(); break;
        default: break;
        }
    }
}

const QMetaObject *AuthManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuthManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AuthManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AuthManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AuthManager::usernameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AuthManager::authStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AuthManager::statusMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AuthManager::loginSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void AuthManager::loginFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void AuthManager::registerSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void AuthManager::registerFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
