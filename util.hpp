#ifndef UTIL_HPP
#define UTIL_HPP

#define MK_FNPTR(R, P, name) R(*name)(meta::MetaInfo, P)
#define MK_FNPTR_T(R, P) R(*)(meta::MetaInfo, P)
#define NO_PARAMS const NullType
#define NO_RETURN NullType
#define META_METHOD(N, R, P) R N(meta::MetaInfo info, P args)
#define Q(...) __VA_ARGS__

#include <typeinfo>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#include "comp_util.hpp"
#include "polywrapper.hpp"

using namespace std;

struct NullType
{
    NullType(){}
    template<typename T> NullType(const T&){}
    template<typename T> operator T() const
    {
        return T();
    }
};
const NullType NullValue=NullType();
const NullType Nothing=NullType();

class ITypeInfo
{
public:
    virtual ~ITypeInfo(){}
    virtual bool operator==(const ITypeInfo &rhs) const=0;
    virtual bool operator!=(const ITypeInfo &rhs) const=0;
    virtual bool before(const ITypeInfo &rhs) const=0;
    virtual string Name() const=0;
    virtual const type_info& Info() const=0;
};

template<typename T> class TypeInfo : public ITypeInfo
{
public:
    bool operator==(const ITypeInfo &rhs) const
    {
        return typeid(T)==rhs.Info();
    }
    bool operator!=(const ITypeInfo &rhs) const
    {
        return typeid(T)!=rhs.Info();
    }
    bool before(const ITypeInfo &rhs) const
    {
        return typeid(T).before(rhs.Info());
    }
    string Name() const
    {
        return demangle(typeid(T).name());
    }
    const type_info& Info() const
    {
        return typeid(T);
    }
};

template<typename T> const ITypeInfo& TypeID(const T&)
{
    return TypeID<T>();
}
template<typename T> const ITypeInfo& TypeID()
{
    static TypeInfo<T> ti;
    return ti;
}

template<typename T> PolyWrapper<ITypeInfo> TypeID2(const T&)
{
    return TypeID2<T>();
}
template<typename T> PolyWrapper<ITypeInfo> TypeID2()
{
    static TypeInfo<T> ti;
    return ti;
}

#endif // UTIL_HPP
