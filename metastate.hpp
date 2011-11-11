#ifndef METASTATE_HPP_INCLUDED
#define METASTATE_HPP_INCLUDED

#include <map>
#include <boost/any.hpp>

namespace meta
{

    //! The state of an object
    struct MetaState
    {
        std::map<std::string, boost::any> Members; //!< A mapping of object member variables
    };

}
#endif // METASTATE_HPP_INCLUDED
