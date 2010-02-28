#include "caller.hpp"
#include "exceptions.hpp"

using namespace std;
using namespace boost;

namespace meta
{

    void Caller::operator()() const
    {
        if (!_fn().TypeCheck(TypeID<NO_RETURN>(), TypeID<NO_PARAMS>()))
        {
            throw Exceptions::TypeMismatch();
        }
        _context.ManyArgs=MkConvert(many());
        MetaInfo ifo(_state, _context);
        _fn().Call(ifo, any(NullValue));
    }

    void Caller::Call() const
    {
        operator()();
    }

    any Caller::operator()(many args) const
    {
        _context.ManyArgs=MkConvert(args);
        MetaInfo ifo(_state, _context);
        return _fn().Call(ifo, args);
    }

    any Caller::Call(many args) const
    {
        return operator()(args);
    }

    string Caller::GetName() const
    {
        return _mname;
    }

    const ITypeInfo& Caller::GetReturnType() const
    {
        return _fn().GetReturnType();
    }
}
