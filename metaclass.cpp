#include "metaclass.hpp"
#include "metaobject.hpp"
#include "exceptions.hpp"

MetaObject New(const MetaClass &cls){
    MetaObject mo(cls);
    mo.CallCtor();
    return mo;
}

string MetaClass::GetName() const{
    return _name;
}

Caller MetaClass::operator[](const string &mname){
    if(_methods.find(mname)==_methods.end()) throw Exceptions::NoSuchMethod();
    if(!_methods[mname]().IsStatic()) throw Exceptions::InstanceRequired();
    return Caller(mname, _methods[mname], MetaContext(mname, *this), _staticstate);
}

bool MetaClass::HasMethod(const string &mname) const{
    return !(_methods.find(mname)==_methods.end());
}

bool MetaClass::IsStatic(const string &mname) const{
    return _methods.find(mname)->second().IsStatic();
}
