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

namespace meta
{

    typedef void(*void_fn)();

    class MetaObject;
    class MetaState;
    class Caller;

    //! Method information
    /*!
        Class that holds information about a method, for reflection
    */
    class MethodInfo
    {
        friend class MetaClass;
    private:
        MethodInfo(string name, PolyWrapper<ITypeInfo> rettype, vector<PolyWrapper<ITypeInfo> > paramtypes) :
                _name(name), _rettype(rettype), _paramtypes(paramtypes) {}
        string _name;
        PolyWrapper<ITypeInfo> _rettype;
        vector<PolyWrapper<ITypeInfo> > _paramtypes;
    public:
        /*!
            Constructor
        */
        MethodInfo() {}
        /*!
            Get the method name
            \return The method name
        */
        string GetName() const;
        /*!
            Get the method return type
            \return The method return type
        */
        PolyWrapper<ITypeInfo> GetReturnType() const;
        /*!
            Get the method parameter types
            \return The method paramter types (tuple)
        */
        vector<PolyWrapper<ITypeInfo> > GetParamTypes() const;
        /*!
            Get a specific parameter type
            \param i    The number of the parameter
            \return The type of the parameter
        */
        PolyWrapper<ITypeInfo> GetParamType(int i) const;
        /*!
            Create a caller for this method
            \param obj  The object to call against
            \return A caller for this method
        */
        Caller MakeCaller(const MetaObject &obj) const;

        //! Equality test
        bool operator==(const MethodInfo &rhs) const;
        //! Inequality test
        bool operator!=(const MethodInfo &rhs) const;
    };

    //! A Meta class
    /*!
        A Meta class, a collection of methods and a static state
    */
    class MetaClass
    {
        friend MetaObject New(const MetaClass &cls);
        string _name;
        MetaState _staticstate;

    protected:
        map<string, PolyWrapper<IFnWrap> > _methods;

    public:
        /*!
            Default constructor, creates an invalid class
        */
        MetaClass() : _name("INVALID CLASS"){}
        /*!
            Constructor
            \param name     The name of the class
        */
        MetaClass(const string &name) : _name(name){}
        /*!
            Add a method to this class
            \param mnane    The method name
            \param fn       An IFnWrap object for the method
        */
        void AddMethod(const string &mname, PolyWrapper<IFnWrap> fn)
        {
            fn().SetStatic(false);
            _methods[mname]=fn;
        }
        /*!
            Add a static function to this class
            \param mname    The function name
            \param fn       An IFnWrap object for the function
        */
        void AddStatic(const string &mname, PolyWrapper<IFnWrap> fn)
        {
            fn().SetStatic(true);
            _methods[mname]=fn;
        }
        /*!
            Get the class name
            \return The class name
        */
        string GetName() const;
        /*!
            Indexing operator to return static function caller
            \param mname    The function name
            \return A caller for the function
        */
        virtual Caller operator[](const string &mname);
        /*!
            Check whether this class has a specific method
            \param mname    The method name
            \return true if this class has the method, false otherwise
        */
        bool HasMethod(const string &mname) const;
        /*!
            Check if a particular method is static
            \param mname    The method name
            \return true if the method is static, false otherwise
        */
        bool IsStatic(const string &mname) const;
        /*!
            Check a method type
            \param Tret     The return type
            \param Tparam   The arguement tuple type
            \param mname    The method name
            \return false if the typecheck fails, true otherwise
        */
        template<typename Tret, typename Tparam> bool TypeCheck(string mname) const
        {
            return _methods.find(mname)->second().TypeCheck(TypeID<Tret>(), TypeID<Tparam>());
        }

        /*!
            Get information for all methods in the class
            \return a mapping of method names to MethodInfo objects
        */
        map<string, MethodInfo> GetMethodInfo() const;
        /*!
            Get information about a specific method
            \param method   The method name
            \return The MethodInfo for the method
        */
        MethodInfo GetMethodInfo(const string &method) const;
    };
}
#endif // METACLASS_HPP
