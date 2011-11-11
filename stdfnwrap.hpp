#ifndef STDFNWRAP_HPP
#define STDFNWRAP_HPP

#include "polywrapper.hpp"
#include "fnwrap.hpp"
#include "tuple_util.hpp"

namespace meta
{

    /*!
        An IFnWrap for a normal C++ free function
        \param Tret     The function return type
        \param Tparam   The function parameter type (a tuple)
    */
    template <typename Tret, typename Tparam>
    class StdFnWrap : public IFnWrap
    {
    private:
        MK_FNPTR(Tret, Tparam, _fnptr);
    public:
        /*!
            Constructor
            \param fnptr    Pointer to a C++ function
        */
        StdFnWrap(MK_FNPTR(Tret, Tparam, fnptr)): _fnptr(fnptr) {}
        /*!
            Check the method types
            \param retType      The return type to test
            \param paramType    The parameter types to test (as a tuple type)
            \return false if the typecheck fails, true if it succeeds
        */
        bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType)
        {
            if (retType==TypeID<Tret>() && paramType==TypeID<Tparam>()) return true;
            else return false;
        }

        /*!
            Get the method return type
            \return The method return type
        */
        PolyWrapper<ITypeInfo> GetReturnType()
        {
            return TypeID2<Tret>();
        }
        /*!
            Get the method parameter types
            \return The method parameter types
        */
        std::vector<PolyWrapper<ITypeInfo> > GetParamTypes()
        {
            return TupleTypes<Tparam>();
        }

        /*!
            Call the method with tuple arguements
            \param info     The call information
            \param args     The method arguements as a tuple wrapped in an any
            \return The method return value wrapped in an any
        */
        boost::any Call(MetaInfo &info, boost::any args)
        {
            return _fnptr(info, boost::any_cast<Tparam>(args));
        }
        /*!
            Call the method with vector<any> arguements
            \param info     The call information
            \param args     The method arguements as a vector<any>
            \return The method return value wrapped in any any
        */
        boost::any Call(MetaInfo &info, many args)
        {
            return Call(info, many_to_tuple<Tparam>(args));
        }
    };

    /*!
        An IFnWrap for a normal C++ free function
        \param Tret     The function return type
    */
    template <typename Tret>
    class StdFnWrap<Tret, NullType> : public IFnWrap
    {
    private:
        typedef NullType Tparam;
        MK_FNPTR(Tret, Tparam, _fnptr);
    public:
        /*!
            Constructor
            \param fnptr    Pointer to a C++ function
        */
        StdFnWrap(MK_FNPTR(Tret, Tparam, fnptr)): _fnptr(fnptr) {}
        bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType)
        {
            if (retType==TypeID<Tret>() && paramType==TypeID<Tparam>()) return true;
            else return false;
        }

        /*!
            Get the method return type
            \return The method return type
        */
        PolyWrapper<ITypeInfo> GetReturnType()
        {
            return TypeID2<Tret>();
        }
        /*!
            Get the method parameter types
            \return The method parameter types
        */
        std::vector<PolyWrapper<ITypeInfo> > GetParamTypes()
        {
            return std::vector<PolyWrapper<ITypeInfo> >();
        }

        /*!
            Call the method with tuple arguements
            \param info     The call information
            \param args     The method arguements as a tuple wrapped in an any
            \return The method return value wrapped in an any
        */
        boost::any Call(MetaInfo &info, boost::any args)
        {
            return _fnptr(info, boost::any_cast<Tparam>(args));
        }
        /*!
            Call the method with vector<any> arguements
            \param info     The call information
            \param args     The method arguements as a vector<any>
            \return The method return value wrapped in any any
        */
        boost::any Call(MetaInfo &info, many args)
        {
            return Call(info, boost::any(NullValue));
        }
    };

    /*!
        Factory function for StdFnWrap
        \param fn   A function pointer
        \return A StdFnWrap wrapping the function pointer
    */
    template<typename Tret, typename Tparam> PolyWrapper<IFnWrap> StdFn(MK_FNPTR(Tret, Tparam, fn))
    {
        return StdFnWrap<Tret, Tparam>(fn);
    }
}
#endif // STDFNWRAP_HPP
