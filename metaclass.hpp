#ifndef METACLASS_HPP
#define METACLASS_HPP

#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include <boost/tuple/tuple.hpp>

#include "util.hpp"
#include "polywrapper.hpp"
#include "fnwrap.hpp"
#include "metacontext.hpp"
#include "caller.hpp"

using namespace std;
using namespace boost;

typedef void(*void_fn)();

class MetaObject;
class MetaState;
class Caller;

class MetaClass{
    friend MetaObject New(const MetaClass &cls);
    string _name;
    MetaState _staticstate;

    protected:
    map<string, PolyWrapper<IFnWrap> > _methods;

    public:
    MetaClass(const string &name) : _name(name){}
    void AddMethod(const string &mname, PolyWrapper<IFnWrap> fn){
        fn().SetStatic(false);
        _methods[mname]=fn;
    }
    void AddStatic(const string &mname, PolyWrapper<IFnWrap> fn){
        fn().SetStatic(true);
        _methods[mname]=fn;
    }
    string GetName() const;
    virtual Caller operator[](const string &mname);
    bool HasMethod(const string &mname) const;
    bool IsStatic(const string &mname) const;
    template<typename Tret, typename Tparam> bool TypeCheck(string mname) const{
        return _methods.find(mname)->second().TypeCheck(TypeID<Tret>(), TypeID<Tparam>());
    }
};

#endif // METACLASS_HPP
