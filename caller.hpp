#ifndef CALLER_HPP_INCLUDED
#define CALLER_HPP_INCLUDED

#include <string>

#include "util.hpp"
#include "metacontext.hpp"
#include "metaclass.hpp"
#include "tuple_util.hpp"
#include "exceptions.hpp"

using namespace std;

class Caller
{
private:
    string _mname;
    PolyWrapper<IFnWrap> _fn;
    mutable MetaContext _context;
    mutable MetaState &_state;
public:
    Caller(const string &mname, PolyWrapper<IFnWrap> fn, MetaContext context, MetaState &state) :
            _mname(mname), _fn(fn), _context(context), _state(state) {}

    template<typename Tret, typename Tparam> Tret operator()(Tparam arg) const
    {
        if (!_fn().TypeCheck(TypeID<Tret>(),TypeID<Tparam>()))
        {
            throw Exceptions::TypeMismatch();
        }
        _context.ManyArgs=MkConvert(arg);
        MetaInfo ifo(_state, _context);
        if (TypeID<Tret>()==TypeID<NO_RETURN>())
        {
            _fn().Call(ifo,arg);
            return Nothing;
        }
        else return any_cast<Tret>(_fn().Call(ifo, arg));
    }
    template<typename Tret, typename Tparam> Tret Call(Tparam arg) const
    {
        return operator()<Tret>(arg);
    }
    template<typename Tret> Tret operator()(many args) const
    {
        _context.ManyArgs=MkConvert(args);
        MetaInfo ifo(_state, _context);
        return any_cast<Tret>(_fn().Call(ifo, args));
    }
    template<typename Tret> Tret Call(many args) const
    {
        return operator()<Tret>(args);
    }
    template<typename Tparam> void operator()(Tparam arg) const
    {
        operator()<NO_RETURN>(arg);
    }
    template<typename Tparam> void Call(Tparam arg) const
    {
        operator()<Tparam>(arg);
    }
    template<typename Tret> Tret operator()() const
    {
        return operator()<Tret>(NullValue);
    }
    template<typename Tret> Tret Call() const
    {
        return operator()<Tret>();
    }
    template<typename Tret, typename Tparam> bool TypeCheck()
    {
        return _fn().TypeCheck(TypeID<Tret>(),TypeID<Tparam>());
    }
    any operator()(many args) const;
    any Call(many args) const;
    void operator()() const;
    void Call() const;
    string GetName() const;
    const ITypeInfo& GetReturnType() const;
    vector<PolyWrapper<ITypeInfo> > GetParamTypes() const;

};

#endif // CALLER_HPP_INCLUDED
