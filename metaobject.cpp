#include "metaobject.hpp"
#include "exceptions.hpp"

namespace meta
{

    MetaObject::MetaObject(const MetaObject &o): MetaClass(o), _state(o._state)
    {
    }

    MetaObject::~MetaObject()
    {
        if (_methods.find("dtor")==_methods.end()) return;
        operator[]("dtor").Call();
    }

    void MetaObject::CallCtor()
    {
        if (_methods.count("ctor")==1)operator[]("ctor")();
    }

    MetaObject MetaObject::Copy() const
    {
        MetaObject mo(*this);
        MetaState *newstate=new MetaState(*this->_state);
        mo._state.reset(newstate);
        return mo;
    }

    Caller MetaObject::operator[](const std::string &mname) const
    {
        if (_methods.find(mname)==_methods.end()) throw Exceptions::NoSuchMethod();
        return Caller(mname, _methods.find(mname)->second, MetaContext(mname, *this), *_state);
    }

    MetaState& MetaObject::GetState() const{
        return *_state;
    }
}
