#ifndef POLYWRAPPER_HPP
#define POLYWRAPPER_HPP

//! An abstract interface for PolyInner
class IPolyInner
{
public:
    virtual IPolyInner* Copy()=0;
    virtual void* Get()=0;
    virtual ~IPolyInner(){}
};

//! A generic holder class for PolyWrapper
template<typename T> class PolyInner : public IPolyInner
{
private:
    T *v;
public:
    PolyInner(const T *o) : v(new T(*o)){}
    IPolyInner* Copy()
    {
        return new PolyInner<T>(v);
    }
    void* Get()
    {
        return static_cast<void*>(v);
    }
    ~PolyInner()
    {
        delete v;
    }
};

//! A wrapper to hold pointers to heap-allocated objects on the stack
/*!
    A wrapper to hold a pointer to a heap allocated object.
    When this object is copied, so is the heap allocated object it points to.
    \param T A base class that the heap-allocated objects should derive from
*/
template<typename T> class PolyWrapper
{
private:
    IPolyInner* v;
public:
    /*!
        Constructor
        \param o An object to copy on the stack, the type of o (To) should derive from T
    */
    template<typename To> PolyWrapper(const To &o): v(new PolyInner<To>(&o)) {}
    /*!
        Default constructor, creates a NULL PolyWrapper
    */
    PolyWrapper(): v(NULL) {}
    /*!
        Copy constructor
        \param o The object to copy
    */
    PolyWrapper(const PolyWrapper<T> &o)
    {
        if (o.v) v=o.v->Copy();
        else v=NULL;
    }

    /*!
        Assignment operator
        \param o The object to assign to this
    */
    PolyWrapper<T>& operator=(const PolyWrapper<T> &o)
    {
        if (v) delete v;
        if (o.v) v=o.v->Copy();
        else v=NULL;
        return *this;
    }

    /*!
        Conversion to T reference
        \return A reference to the object
    */
    operator T&() const
    {
        return *static_cast<T*>(v->Get());
    }
    /*!
        () operator
        \return A refernce to the object
    */
    T& operator()() const
    {
        return *static_cast<T*>(v->Get());
    }
    /*!
        Get the object
        \return A reference to the object
    */
    T& Get() const
    {
        return *static_cast<T*>(v->Get());
    }
    /*!
        -> operator
        \return A pointer to the object
    */
    T* operator->() const{
        return static_cast<T*>(v->Get());
    }

    /*!
        Destructor
    */
    ~PolyWrapper()
    {
        if (v) delete v;
    }
};

#endif // POLYWRAPPER_HPP
