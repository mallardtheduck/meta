#ifndef DBGFNWRAP_HPP
#define DBGFNWRAP_HPP

#include <typeinfo>
#include <iostream>
#include <vector>
#include "comp_util.hpp"
#include "util.hpp"
#include "fnwrap.hpp"

using namespace std;

template <typename Tret, typename Tparam>
        class DbgFnWrap : public IFnWrap{
    public:
    bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType){
        if(retType==TypeID<Tret>() && paramType==TypeID<Tparam>()) return true;
        else return false;
    }


    const ITypeInfo& GetReturnType(){
        return TypeID<Tret>();
    }
    vector<PolyWrapper<ITypeInfo> > GetParamTypes(){
        return TupleTypes<Tparam>();
    }

    any Call(MetaInfo &info, any args){
        const Tparam &cargs=any_cast<Tparam>(args);
        cout << "Meta function call to: " << info.Context.Class.GetName() << "::" << info.Context.MethodName << endl;
        if(_static) cout << "Method is STATIC." << endl;
        cout << "Argument types:" << endl;
        OutTupleTypes(Tparam());
        cout << "Arguments:" << (Tparam)cargs << endl;
        cout << "Return type:" << TypeID<Tret>().Name() << endl;
        return Tret();
    }
    any Call(MetaInfo &info, many args){
        return Call(info, many_to_tuple<Tparam>(args));
    }
};

template <typename Tret>
        class DbgFnWrap<Tret, const NullType> : public IFnWrap{
    public:
    bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType){
        if(retType==TypeID<Tret>() && paramType==TypeID<const NullType>()) return true;
        else return false;
    }
    any Call(MetaInfo &info, any args){
        cout << "Meta function call to: " << info.Context.Class.GetName() << "::" << info.Context.MethodName << endl;
        if(_static) cout << "Method is STATIC." << endl;
        cout << "No arguements." << endl;
        cout << "Return type:" << TypeID<Tret>().Name() << endl;
        return Tret();
    }

    const ITypeInfo& GetReturnType(){
        return TypeID<Tret>();
    }
    vector<PolyWrapper<ITypeInfo> > GetParamTypes(){
        return vector<PolyWrapper<ITypeInfo> >();
    }

    any Call(MetaInfo &info, many args){
        return Call(info, any(NullValue));
    }
};


#endif // DBGFNWRAP_HPP
