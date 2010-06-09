#ifndef METASTATE_HPP_INCLUDED
#define METASTATE_HPP_INCLUDED

#include <map>
#include <boost/any.hpp>

using namespace std;
using namespace boost;

namespace meta
{

    //! The state of an object
    struct MetaState
    {
        map<string, any> Members; //!< A mapping of object member variables
    };

}
#endif // METASTATE_HPP_INCLUDED
