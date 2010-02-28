#ifndef STDFNWRAP_HPP
#define STDFNWRAP_HPP

#include "polywrapper.hpp"
#include "fnwrap.hpp"
#include "tuple_util.hpp"

using namespace std;

template <typename Tret, typename Tparam>
class StdFnWrap : public IFnWrap{
    private:
    MK_FNPTR(Tret, Tparam, _fnptr);
    public:
    StdFnWrap(MK_FNPTR(Tret, Tparam, fnptr)): _fnptr(fnptr) {}
    bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType){
        if(retType==TypeID<Tret>() && paramType==TypeID<Tparam>()) return true;
        else return false;
    }

    PolyWrapper<ITypeInfo> GetReturnType(){
        return TypeID2<Tret>();
    }
    vector<PolyWrapper<ITypeInfo> > GetParamTypes(){
        return TupleTypes<Tparam>();
    }

    any Call(MetaInfo &info, any args){
        return _fnptr(info, any_cast<Tparam>(args));
    }
    any Call(MetaInfo &info, many args){
        return Call(info, many_to_tuple<Tparam>(args));
    }
};

template <typename Tret>
class StdFnWrap<Tret, NullType> : public IFnWrap{
    private:
    typedef NullType Tparam;
    MK_FNPTR(Tret, Tparam, _fnptr);
    public:
    StdFnWrap(MK_FNPTR(Tret, Tparam, fnptr)): _fnptr(fnptr) {}
    bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType){
        if(retType==TypeID<Tret>() && paramType==TypeID<Tparam>()) return true;
        else return false;
    }

    PolyWrapper<ITypeInfo> GetReturnType(){
        return TypeID2<Tret>();
    }
    vector<PolyWrapper<ITypeInfo> > GetParamTypes(){
        return vector<PolyWrapper<ITypeInfo> >();
    }


    any Call(MetaInfo &info, any args){
        return _fnptr(info, any_cast<Tparam>(args));
    }
    any Call(MetaInfo &info, many args){
        return Call(info, any(NullValue));
    }
};

template<typename Tret, typename Tparam> PolyWrapper<IFnWrap> StdFn(MK_FNPTR(Tret, Tparam, fn)){
    return StdFnWrap<Tret, Tparam>(fn);
}

#endif // STDFNWRAP_HPP
