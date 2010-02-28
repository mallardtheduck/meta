#ifndef METACONTEXT_HPP
#define METACONTEXT_HPP

#include <string>
#include <map>

#include <boost/any.hpp>

#include "metastate.hpp"
#include "metaclass.hpp"
#include "tuple_util.hpp"

#define MEM_INIT(t,x) info.State.Members[#x]=t(); MEM(t,x)
#define MEM_INIT_VAL(t,x,v) info.State.Members[#x]=t(v); MEM(t,x)
#define MEM(t,x) t &x=any_cast<t&>(info.State.Members[#x])

using namespace std;
using namespace boost;

namespace meta
{

    class MetaObject;
    class MetaClass;

    struct MetaContext
    {
        string MethodName;
        const MetaClass &Class;
        PolyWrapper<ITupleManyConvert> ManyArgs;
        MetaContext(string mname, const MetaClass &cls) :
                MethodName(mname),  Class(cls) {}
    };

    struct MetaInfo
    {
        MetaState &State;
        MetaContext Context;
        MetaInfo(MetaState &state, MetaContext context):State(state), Context(context){}
    };

}
#endif // METACONTEXT_HPP
