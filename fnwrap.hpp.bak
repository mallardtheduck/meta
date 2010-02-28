#ifndef FNWRAP_HPP
#define FNWRAP_HPP

#include <iostream>
#include <typeinfo>
#include <boost/any.hpp>
#include <boost/tuple/tuple_io.hpp>

#include "util.hpp"
#include "polywrapper.hpp"
#include "metacontext.hpp"

#include "tuple_util.hpp"

using namespace boost;
using namespace std;
using namespace tuples;

class MetaInfo;

class IFnWrap{
    protected:
    bool _static;
    public:
    IFnWrap() : _static(false) {}
    virtual bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType)=0;
    virtual any Call(MetaInfo &info, any args)=0;
    virtual any Call(MetaInfo &info, many args)=0;

    virtual const ITypeInfo& GetReturnType()=0;
    virtual vector<PolyWrapper<ITypeInfo> > GetParamTypes()=0;

    virtual bool IsStatic(){return _static;}
    virtual void SetStatic(bool s){_static=s;}
    virtual ~IFnWrap(){}
};

#endif // FNWRAP_HPP
