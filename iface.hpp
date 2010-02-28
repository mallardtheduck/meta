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

    class IIfaceMethod
    {
    public:
        virtual bool HasMatch(const MetaClass &) const=0;
        virtual ~IIfaceMethod(){}
    };

    template<typename Tret, typename Tparam> class IfaceMethod : public IIfaceMethod
    {
    private:
        string _name;
        bool _static;
    public:
        IfaceMethod(const string &name) : _name(name), _static(false) {}
        IfaceMethod(const string &name, bool stic) : _name(name), _static(stic) {}
        bool HasMatch(const MetaClass &cls) const
        {
            return cls.HasMethod(_name) && cls.TypeCheck<Tret, Tparam>(_name) && cls.IsStatic(_name)==_static;
        }
    };

    class MetaIface
    {
    private:
        vector<PolyWrapper<IIfaceMethod> > _methods;
    public:
        void AddMethod(const PolyWrapper<IIfaceMethod> &method)
        {
            _methods.push_back(method);
        }
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
