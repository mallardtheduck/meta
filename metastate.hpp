#ifndef METASTATE_HPP_INCLUDED
#define METASTATE_HPP_INCLUDED

#include <map>
#include <boost/any.hpp>

using namespace std;
using namespace boost;

namespace meta
{

    struct MetaState
    {
        map<string, any> Members;
    };

}
#endif // METASTATE_HPP_INCLUDED
