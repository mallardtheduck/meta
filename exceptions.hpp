#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <stdexcept>

using namespace std;

namespace meta
{
    namespace Exceptions
    {
        //! A type check has failed
        class TypeMismatch : public std::exception {};
        //! The method requested does not exist
        class NoSuchMethod : public std::exception {};
        //! A non-static method has been called against a class
        class InstanceRequired : public std::exception {};
    }
}
#endif // EXCEPTIONS_HPP_INCLUDED
