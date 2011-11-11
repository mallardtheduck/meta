#include "metaclass.hpp"
#include "metaobject.hpp"
#include "exceptions.hpp"

namespace meta
{

    MetaObject New(const MetaClass &cls)
    {
        MetaObject mo(cls);
        mo.CallCtor();
        return mo;
    }

    MetaObject *NewPtr(const MetaClass &cls)
    {
        MetaObject *mo=new MetaObject(cls);
        mo->CallCtor();
        return mo;
    }

    std::string MetaClass::GetName() const
    {
        return _name;
    }

    Caller MetaClass::operator[](const std::string &mname)
    {
        if (_methods.find(mname)==_methods.end()) throw Exceptions::NoSuchMethod();
        if (!_methods[mname]().IsStatic()) throw Exceptions::InstanceRequired();
        return Caller(mname, _methods[mname], MetaContext(mname, *this), _staticstate);
    }

    bool MetaClass::HasMethod(const std::string &mname) const
    {
        return !(_methods.find(mname)==_methods.end());
    }

    bool MetaClass::IsStatic(const std::string &mname) const
    {
        return _methods.find(mname)->second().IsStatic();
    }

    std::map<std::string, MethodInfo> MetaClass::GetMethodInfo() const
    {
        std::map<std::string, MethodInfo> ret;
        foreach(Q(std::pair<std::string, PolyWrapper<IFnWrap> >) meth, _methods)
        {
            ret.insert(std::make_pair(meth.first, MethodInfo(meth.first, meth.second().GetReturnType(), meth.second().GetParamTypes())));
        }
        return ret;
    }

    MethodInfo MetaClass::GetMethodInfo(const std::string &method) const
    {
        PolyWrapper<IFnWrap> fn=_methods.find(method)->second;
        return MethodInfo(method, fn().GetReturnType(), fn().GetParamTypes());
    }

    std::string MethodInfo::GetName() const
    {
        return _name;
    }

    PolyWrapper<ITypeInfo> MethodInfo::GetReturnType() const
    {
        return _rettype;
    }

    std::vector<PolyWrapper<ITypeInfo> > MethodInfo::GetParamTypes() const
    {
        return _paramtypes;
    }

    PolyWrapper<ITypeInfo> MethodInfo::GetParamType(int i) const
    {
        return _paramtypes[i];
    }

    Caller MethodInfo::MakeCaller(const MetaObject &obj) const
    {
        if (obj.GetMethodInfo(_name)!=*this) throw Exceptions::NoSuchMethod();
        return obj[_name];
    }

    bool MethodInfo::operator==(const MethodInfo &rhs) const
    {
        if (_name!=rhs._name) return false;
        if (_rettype()!=rhs._rettype()) return false;
        if (_paramtypes.size()!=rhs._paramtypes.size()) return false;
        for (size_t i=0; i<_paramtypes.size(); i++)
        {
            if (_paramtypes[i]()!=rhs._paramtypes[i]()) return false;
        }
        return true;
    }

    bool MethodInfo::operator!=(const MethodInfo &rhs) const
    {
        return !(*this==rhs);
    }
}
