#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <stdexcept>

using namespace std;

namespace meta
{
    namespace Exceptions
    {
        class TypeMismatch : public exception {};
        class NoSuchMethod : public exception {};
        class InstanceRequired : public exception {};
    }
}
#endif // EXCEPTIONS_HPP_INCLUDED
