/****************************************************************************
** Meta object code from reading C++ file 'AssetResolver.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Data/AssetResolver.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AssetResolver.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13AssetResolverE_t {};
} // unnamed namespace

template <> constexpr inline auto AssetResolver::qt_create_metaobjectdata<qt_meta_tag_ZN13AssetResolverE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AssetResolver",
        "resolveCardImage",
        "",
        "cardId",
        "resolveCharacterImage",
        "charId",
        "resolveElementIcon",
        "ElementType",
        "element",
        "resolveWeatherIcon",
        "WeatherType",
        "weather",
        "resolveWeatherName",
        "resolveWeatherDescription"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'resolveCardImage'
        QtMocHelpers::MethodData<QString(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 3 },
        }}),
        // Method 'resolveCharacterImage'
        QtMocHelpers::MethodData<QString(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 5 },
        }}),
        // Method 'resolveElementIcon'
        QtMocHelpers::MethodData<QString(ElementType)>(6, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Method 'resolveWeatherIcon'
        QtMocHelpers::MethodData<QString(WeatherType)>(9, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'resolveWeatherName'
        QtMocHelpers::MethodData<QString(WeatherType)>(12, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'resolveWeatherDescription'
        QtMocHelpers::MethodData<QString(WeatherType)>(13, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 10, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AssetResolver, qt_meta_tag_ZN13AssetResolverE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AssetResolver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AssetResolverE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AssetResolverE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13AssetResolverE_t>.metaTypes,
    nullptr
} };

void AssetResolver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AssetResolver *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QString _r = _t->resolveCardImage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 1: { QString _r = _t->resolveCharacterImage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->resolveElementIcon((*reinterpret_cast<std::add_pointer_t<ElementType>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->resolveWeatherIcon((*reinterpret_cast<std::add_pointer_t<WeatherType>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->resolveWeatherName((*reinterpret_cast<std::add_pointer_t<WeatherType>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->resolveWeatherDescription((*reinterpret_cast<std::add_pointer_t<WeatherType>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *AssetResolver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AssetResolver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AssetResolverE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AssetResolver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
