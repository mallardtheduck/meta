#ifndef IFACE_HPP_INCLUDED
#define IFACE_HPP_INCLUDED

#include <string>
#include <vector>
#include "metaclass.hpp"
#include "caller.hpp"
#include "polywrapper.hpp"
#include "util.hpp"

using namespace std;

namespace meta
{

    //! Interface for method specifacations in MetaIface
    /*!
        Interface for Meta Interface method specifacations.
    */
    class IIfaceMethod
    {
    public:
        /*!
            Test whether a class has a method matching this one
            \param cls A MetaClass to test
            \return true if the class has a matching method, false otherwise
        */
        virtual bool HasMatch(const MetaClass &cls) const=0;
        virtual ~IIfaceMethod(){}
    };

    //! Implementation of a MetaIface method specifacation
    /*!
        The implementation of a method specifacation for a Meta Interface
        \param Tret     The method return type
        \param Tparam   The method parameter types as a tuple
    */
    template<typename Tret, typename Tparam> class IfaceMethod : public IIfaceMethod
    {
    private:
        string _name;
        bool _static;
    public:
        /*!
            Constructor
            \param name     The method name
        */
        IfaceMethod(const string &name) : _name(name), _static(false) {}
        /*!
            Constructor
            \param name     The method name
            \param stic     true if the method is static, false otherwise
        */
        IfaceMethod(const string &name, bool stic) : _name(name), _static(stic) {}

        /*!
            Test whether a class has a method matching this one
            \param cls A MetaClass to test
            \return true if the class has a matching method, false otherwise
        */
        bool HasMatch(const MetaClass &cls) const
        {
            return cls.HasMethod(_name) && cls.TypeCheck<Tret, Tparam>(_name) && cls.IsStatic(_name)==_static;
        }
    };

    //! A Meta interface
    /*!
        A meta interface, contains method specifacations
    */
    class MetaIface
    {
    private:
        vector<PolyWrapper<IIfaceMethod> > _methods;
    public:
        /*!
            Add a method specifacation to this interface
            \param method   The method specifacation
        */
        void AddMethod(const PolyWrapper<IIfaceMethod> &method)
        {
            _methods.push_back(method);
        }
        /*!
            Check a class to see whether it matches this interface
            \param cls  The class to check
            \return true if the class matches, false otherwise
        */
        bool IsMatch(const MetaClass &cls) const
        {
            foreach(PolyWrapper<IIfaceMethod> m, _methods)
            {
                if (!m().HasMatch(cls)) return false;
            }
            return true;
        }
    };
}
#endif // IFACE_HPP_INCLUDED
