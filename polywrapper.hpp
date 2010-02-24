#ifndef POLYWRAPPER_HPP
#define POLYWRAPPER_HPP

class IPolyInner{
    public:
    virtual IPolyInner* Copy()=0;
    virtual void* Get()=0;
    virtual ~IPolyInner(){}
};

template<typename T> class PolyInner : public IPolyInner{
    private:
    T *v;
    public:
    PolyInner(const T *o) : v(new T(*o)){}
    IPolyInner* Copy(){
        return new PolyInner<T>(v);
    }
    void* Get(){
        return static_cast<void*>(v);
    }
    ~PolyInner(){
        delete v;
    }
};

template<typename T> class PolyWrapper{
    private:
    IPolyInner* v;
    public:
    template<typename To> PolyWrapper(const To &o): v(new PolyInner<To>(&o)) {}
    PolyWrapper(): v(NULL) {}
    PolyWrapper(const PolyWrapper<T> &o)
    {
        if(o.v) v=o.v->Copy();
            else v=NULL;
    }

    PolyWrapper<T>& operator=(const PolyWrapper<T> &o){
        if(v) delete v;
        if(o.v) v=o.v->Copy();
            else v=NULL;
        return *this;
    }

    operator T&() const{
        return *static_cast<T*>(v->Get());
    }
    T& operator()() const{
        return *static_cast<T*>(v->Get());
    }
    T& Get() const{
        return *static_cast<T*>(v->Get());
    }

    ~PolyWrapper(){
        if(v) delete v;
    }
};

#endif // POLYWRAPPER_HPP
