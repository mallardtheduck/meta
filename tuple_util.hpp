#ifndef TUPLE_UTIL_HPP
#define TUPLE_UTIL_HPP

#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/config.hpp>

#include <vector>

#include "comp_util.hpp"
#include "util.hpp"

typedef std::vector<boost::any> many;

#if !defined(BOOST_NO_VARIADIC_TEMPLATES)

template<typename H> void variadic_to_many(many &m, H head){
    m.push_back(boost::any(head));
}

template<typename H, typename... T> void variadic_to_many(many &m, H head, T... tail){
    m.push_back(boost::any(head));
    variadic_to_many(m, tail...);
}

template<typename... V> many variadic_to_many(V... vars){
    many m;
    variadic_to_many(m, vars...);
    return m;
}

/* Not yet supported by GCC (as of 4.6)
 * 
 * template<typename... A> boost::tuple<A...> MArgs(A... args){
    return boost::tuples::make_tuple(args...);
}*/

#define MArgs(...) __VA_ARGS__

#else

#define MArgs(...) boost::make_tuple(__VA_ARGS__)

#endif

#define MParams(...) boost::tuple<__VA_ARGS__>

//! tuple_to_many terminating case
inline void tuple_to_many(many &m, const boost::tuples::null_type&){}

//! tuple_to_many continuing case
template<typename H, typename T> void tuple_to_many(many &m, const boost::tuples::cons<H, T> &t)
{
    m.push_back(boost::any(t.get_head()));
    tuple_to_many(m, t.get_tail());
}

/*!
    Convert a tuple to a vector<any>
    \param tup  The tuple to convert
    \return A vector<any> equivelent to the tuple
*/
template<typename T> many tuple_to_many(const T tup)
{
    many m;
    tuple_to_many(m, tup);
    return m;
}

//! many_to_tuple terminating case
inline void many_to_tuple(const many &m, size_t i, const boost::tuples::null_type&){}

//! many_to_tuple continueing case
template<typename H, typename T> void many_to_tuple(const many &m, size_t i, boost::tuples::cons<H, T> &t)
{
    t.get_head()=boost::any_cast<H>(m[i]);
    many_to_tuple(m, ++i, t.get_tail());
}

/*!
    Convert a vector<any> to a tuple
    \param m    a vector<many>
    \param T    the type of the tuple to return
    \return A tuple equivelent to the vector<many>
*/
template<typename T> T many_to_tuple(const many &m)
{
    T t;
    many_to_tuple(m,0,t);
    return t;
}

//! Interface for a tuple-to-many conversion object
class ITupleManyConvert
{
public:
    virtual ~ITupleManyConvert(){}
    virtual const many& operator()()=0;
};

//! Template implementation of a tuple-to-many conversion object
/*!
    Acts as a functor to convert a stored tuple to a vector<any>
    \param T    The type of the tuple
*/
template<typename T> class TupleManyConvert : public ITupleManyConvert
{
private:
    const T &_tuple;
    many _many;
    bool _hasmany;
public:
    /*!
        Constructor
        \param tuple    The tuple to store/convert
    */
    TupleManyConvert(const T &tup) : _tuple(tup), _hasmany(false){}
    /*!
        () operator to perform the conversion
        \return a vector<any> equivelent to the tuple
    */
    const many& operator()()
    {
        if (!_hasmany)
        {
            _many=tuple_to_many(_tuple);
        }
        return _many;
    }
};

//! An ITupleManyConvert that returns a stored many
/*!
    A functor for use when the data is already in vector<any> form
*/
template<> class TupleManyConvert<many> : public ITupleManyConvert
{
private:
    const many &_many;
public:
    /*!
        Constructor
        \param some     The vector<any>
    */
    TupleManyConvert(const many &some): _many(some){}
    /*!
        () operator to return the vector<any>
        \return The vector<any>
    */
    const many& operator()()
    {
        return _many;
    }
};


/*!
    TupleManyConvert factory function
    \param tuple    The tuple
    \return a TupleManyConvert object for converting the tuple to a vector<any>
*/
template<typename T> PolyWrapper<ITupleManyConvert> MkConvert(const T &tuple)
{
    return TupleManyConvert<T>(tuple);
}

//! OutTupleTypes terminating case
inline void OutTupleTypes(const boost::tuples::null_type&){}

/*!
    A function to output the types of the values stored in a tuple
    \param tup The tuple
*/
template<typename H, typename T> void OutTupleTypes(const boost::tuples::cons<H, T> &tup)
{
    std::cout << TypeID<H>().Name() << std::endl;
    OutTupleTypes(tup.get_tail());
}

//! TupleTypes terminating case
inline void TupleTypes(const boost::tuples::null_type&, std::vector<PolyWrapper<ITypeInfo> >){}


//! TupleTypes continuing case
template<typename H, typename T> void TupleTypes(const boost::tuples::cons<H, T> &tup, std::vector<PolyWrapper<ITypeInfo> > &vec)
{
    vec.push_back(TypeID2<H>());
    TupleTypes(tup.get_tail(), vec);
}

/*!
    Function to return the types of values stored in a tuple
    \param T    The tuple type
    \return a vector of the tuple types
*/
template<typename T> std::vector<PolyWrapper<ITypeInfo> > TupleTypes()
{
    std::vector<PolyWrapper<ITypeInfo> > vec;
    TupleTypes(T(), vec);
    return vec;
}

#endif // TUPLE_UTIL_HPP
