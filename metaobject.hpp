#ifndef METAOBJECT_HPP
#define METAOBJECT_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <map>

#include <boost/smart_ptr.hpp>
#include <boost/any.hpp>

#include "metaclass.hpp"
#include "metacontext.hpp"
#include "tuple_util.hpp"
#include "caller.hpp"

using namespace std;
using namespace boost;

namespace meta
{

    struct MetaState;
    struct MetaContext;

    class MetaClass;

    class MetaObject : public MetaClass
    {
        friend MetaObject New(const MetaClass &cls);

    private:
        shared_ptr<MetaState> _state;

        MetaObject(const MetaClass &cls): MetaClass(cls.GetName())
        {
            _methods=static_cast<const MetaObject*>(&cls)->_methods;
            _state.reset(new MetaState());
        }
        void CallCtor();

    public:
        MetaObject(const MetaObject &o): MetaClass(o.GetName()), _state(o._state) {}
        Caller operator[](const string &mname) const;
        MetaObject Copy();

        template<typename Tparam> void CallCtor(Tparam param)
        {
            if (_methods.count("ctor")==1) operator[]("ctor").Call<void>(param);
        }
    };
}
#endif // METAOBJECT_HPP
