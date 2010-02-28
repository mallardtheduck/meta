#ifndef COMP_UTIL_HPP_INCLUDED
#define COMP_UTIL_HPP_INCLUDED

#ifdef __GNUC__
#ifndef HAVE_CXA_DEMANGLE
#define HAVE_CXA_DEMANGLE
#endif
#endif

#include <string>

using namespace std;

#ifdef HAVE_CXA_DEMANGLE

#include <cxxabi.h>

/*!
    Convert a GCC typeid::name() into a C++ type name
    \param name the name recieved from typeid::name() in GCC
    \return the C++ type name
*/
inline string demangle(const char* name)
{
    //A 1024-chracter buffer should be large enough, this is only a debugging tool
    char buf[1024];
    size_t size=1024;
    int status;

    //Call the GCC-specific API to do the conversion
    char* res = abi::__cxa_demangle(name, buf, &size, &status);

    //Return the result as a std::string
    return string(res);
}
#else

//For non-GCC compilers, just return the input
inline string demangle(const char* name)
{
    return name;
}
#endif

#endif // COMP_UTIL_HPP_INCLUDED
