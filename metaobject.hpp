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

namespace meta
{

    struct MetaState;
    struct MetaContext;

    class MetaClass;

    //! A Meta object
    /*!
        An instance of a Meta object. A collection of methods, plus state
    */
    class MetaObject : public MetaClass
    {
        friend MetaObject New(const MetaClass &cls);
        friend MetaObject* NewPtr(const MetaClass &cls);

    private:
        boost::shared_ptr<MetaState> _state;

        MetaObject(const MetaClass &cls): MetaClass(cls.GetName())
        {
            _methods=static_cast<const MetaObject*>(&cls)->_methods;
            _state.reset(new MetaState());
        }
        void CallCtor();

    public:
        /*!
            Default constructor, creates an empty object
        */
        MetaObject() : MetaClass("EMPTY_OBJECT") {}
        /*!
            Copy constructor
            \param o The object to copy
        */
        MetaObject(const MetaObject &o);
        /*!
            Destructor
        */
        ~MetaObject();
        /*!
            Indexing operator
            \param mname    The name of a method
            \return A Caller for the method
        */
        Caller operator[](const std::string &mname) const;
        /*!
            Copy the object
            \return A copy of this object
        */
        MetaObject Copy() const;
        /*!
            Get the object state
            \return the object state
        */
        MetaState& GetState() const;
    };
}
#endif // METAOBJECT_HPP
