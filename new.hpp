#ifndef NEW_HPP
#define NEW_HPP

#include "metaclass.hpp"
#include "metaobject.hpp"

MetaObject New(const MetaClass &cls);
template<typename Tparam> MetaObject New(const MetaClass &cls, Tparam param){
    MetaObject mo(cls);
    mo.CallCtor(param);
    return mo;
}

#endif // NEW_HPP
