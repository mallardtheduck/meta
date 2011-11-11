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

namespace meta
{

    class MetaObject;
    class MetaClass;

    //! A Meta method execution context
    /*!
        A struct holding context information for meta method execution
    */
    struct MetaContext
    {
        std::string MethodName;                                  //!< The method name
        const MetaClass &Class;                             //!< The class
        PolyWrapper<ITupleManyConvert> ManyArgs;            //!< A function to retrieve the arguements as a vector<any>
        /*!
            Constructor
            \param mname    The method name
            \param cls      The class
        */
        MetaContext(std::string mname, const MetaClass &cls) :
                MethodName(mname),  Class(cls) {}
    };

    //! Meta call information
    /*!
        A stuct containing information for a Meta call
    */
    struct MetaInfo
    {
        MetaState &State;                                   //!< The object state
        MetaContext Context;                                //!< The execution context
        /*!
            Constructor
            \param state    The object state
            \param context  The execution context
        */
        MetaInfo(MetaState &state, MetaContext context):State(state), Context(context){}
    };

}
#endif // METACONTEXT_HPP
