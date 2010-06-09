#ifndef NEW_HPP
#define NEW_HPP

#include "metaclass.hpp"
#include "metaobject.hpp"

namespace meta
{
    /*!
        Create a new object from a class
        \param cls The class
        \return A new instance of the class
    */
    MetaObject New(const MetaClass &cls);
    /*!
        Create a new object on the heap
        \param cls The class to create an instance of
        \return A pointer to the new instance
    */
    MetaObject *NewPtr(const MetaClass &cls);
}
#endif // NEW_HPP
