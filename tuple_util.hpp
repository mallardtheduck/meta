#ifndef TUPLE_UTIL_HPP
#define TUPLE_UTIL_HPP

#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <vector>
#include "comp_util.hpp"

#include "util.hpp"

using namespace boost;
using namespace tuples;
using namespace std;

typedef vector<any> many;

inline void tuple_to_many(many &m, const null_type&){}

template<typename H, typename T> void tuple_to_many(many &m, const cons<H, T> &t)
{
    m.push_back(any(t.get_head()));
    tuple_to_many(m, t.get_tail());
}

template<typename T> many tuple_to_many(const T tup)
{
    many m;
    tuple_to_many(m, tup);
    return m;
}

inline void many_to_tuple(const many &m, size_t i, const null_type&){}

template<typename H, typename T> void many_to_tuple(const many &m, size_t i, cons<H, T> &t)
{
    t.get_head()=any_cast<H>(m[i]);
    many_to_tuple(m, ++i, t.get_tail());
}

template<typename T> T many_to_tuple(const many &m)
{
    T t;
    many_to_tuple(m,0,t);
    return t;
}

class ITupleManyConvert
{
public:
    virtual ~ITupleManyConvert(){}
    virtual const many& operator()()=0;
};

template<typename T> class TupleManyConvert : public ITupleManyConvert
{
private:
    const T &_tuple;
    many _many;
    bool _hasmany;
public:
    TupleManyConvert(const T &tuple) : _tuple(tuple), _hasmany(false){}
    const many& operator()()
    {
        if (!_hasmany)
        {
            _many=tuple_to_many(_tuple);
        }
        return _many;
    }
};

template<> class TupleManyConvert<many> : public ITupleManyConvert
{
private:
    const many &_many;
public:
    TupleManyConvert(const many &some): _many(some){}
    const many& operator()()
    {
        return _many;
    }
};

template<typename T> PolyWrapper<ITupleManyConvert> MkConvert(const T &tuple)
{
    return TupleManyConvert<T>(tuple);
}

inline void OutTupleTypes(const null_type&){}

template<typename H, typename T> void OutTupleTypes(const cons<H, T> &tup)
{
    cout << TypeID<H>().Name() << endl;
    OutTupleTypes(tup.get_tail());
}

inline void TupleTypes(const null_type&, vector<PolyWrapper<ITypeInfo> >){}

template<typename H, typename T> void TupleTypes(const cons<H, T> &tup, vector<PolyWrapper<ITypeInfo> > &vec)
{
    vec.push_back(TypeID2<H>());
    TupleTypes(tup.get_tail(), vec);
}

template<typename T> vector<PolyWrapper<ITypeInfo> > TupleTypes()
{
    vector<PolyWrapper<ITypeInfo> > vec;
    TupleTypes(T(), vec);
    return vec;
}

#endif // TUPLE_UTIL_HPP
