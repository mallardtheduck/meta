#include "metaobject.hpp"
#include "exceptions.hpp"

namespace meta
{

    void MetaObject::CallCtor()
    {
        if (_methods.count("ctor")==1)operator[]("ctor")();
    }

    MetaObject MetaObject::Copy()
    {
        MetaObject mo(*this);
        MetaState *newstate=new MetaState(*this->_state);
        mo._state.reset(newstate);
        return mo;
    }

    Caller MetaObject::operator[](const string &mname) const
    {
        if (_methods.find(mname)==_methods.end()) throw Exceptions::NoSuchMethod();
        return Caller(mname, _methods.find(mname)->second, MetaContext(mname, *this), *_state);
    }
}
