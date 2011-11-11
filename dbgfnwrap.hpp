#ifndef DBGFNWRAP_HPP
#define DBGFNWRAP_HPP

#include <typeinfo>
#include <iostream>
#include <vector>

#include "comp_util.hpp"
#include "util.hpp"
#include "fnwrap.hpp"

namespace meta
{

    //! Debugging IFnWrap
    /*!
        A IFnWrap for debugging purposes, outputs the call details only.
        \param Tret     The method return type
        \param Tparam   The method parameter types (tuple)
    */
    template <typename Tret, typename Tparam>
    class DbgFnWrap : public IFnWrap
    {
    public:
        /*!
            Check the method types
            \param retType      The return type to test
            \param paramType    The parameter types to test (tuple)
            \return true if the check succeeds, false otherwise
        */
        bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType)
        {
            if (retType==TypeID<Tret>() && paramType==TypeID<Tparam>()) return true;
            else return false;
        }

        /*!
            Get the 'method' return type
            \return     The 'method' return type
        */
        PolyWrapper<ITypeInfo> GetReturnType()
        {
            return TypeID2<Tret>();
        }
        /*!
            Get the 'method' parameter types
            \return The 'method' parameter types
        */
        std::vector<PolyWrapper<ITypeInfo> > GetParamTypes()
        {
            return TupleTypes<Tparam>();
        }

        /*!
            Call function. Outputs the details of the call and returns a default value.
            \param info     The call information
            \param args     The method arguements as a tuple wrapped in an any
            \return A default value
        */
        boost::any Call(MetaInfo &info, boost::any args)
        {
            const Tparam &cargs=boost::any_cast<Tparam>(args);
            std::cout << "Meta function call to: " << info.Context.Class.GetName() << "::" << info.Context.MethodName << std::endl;
            if (_static) std::cout << "Method is STATIC." << std::endl;
            std::cout << "Argument types:" << std::endl;
            OutTupleTypes(Tparam());
            std::cout << "Arguments:" << (Tparam)cargs << std::endl;
            std::cout << "Return type:" << TypeID<Tret>().Name() << std::endl;
            return Tret();
        }
        /*!
            Call function with vector<any> for arguements.
            \param info     The call information
            \param args     The method arguements as a vector<any>
            \return A default value
        */
        boost::any Call(MetaInfo &info, many args)
        {
            return Call(info, many_to_tuple<Tparam>(args));
        }
    };

    //! Debugging IFnWrap
    /*!
        A IFnWrap for debugging purposes, outputs the call details only.
        \param Tret     The method return types
    */
    template <typename Tret>
    class DbgFnWrap<Tret, const NullType> : public IFnWrap
    {
    public:
        /*!
            Check the method types
            \param retType      The return type to test
            \param paramType    The parameter types to test (tuple)
            \return true if the check succeeds, false otherwise
        */
        bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType)
        {
            if (retType==TypeID<Tret>() && paramType==TypeID<const NullType>()) return true;
            else return false;
        }
        /*!
            Call function. Outputs the details of the call and returns a default value.
            \param info     The call information
            \param args     The method arguements as a tuple wrapped in an any
            \return A default value
        */
        boost::any Call(MetaInfo &info, boost::any args)
        {
            std::cout << "Meta function call to: " << info.Context.Class.GetName() << "::" << info.Context.MethodName << std::endl;
            if (_static) std::cout << "Method is STATIC." << std::endl;
            std::cout << "No arguements." << std::endl;
            std::cout << "Return type:" << TypeID<Tret>().Name() << std::endl;
            return Tret();
        }

        /*!
            Get the 'method' return type
            \return     The 'method' return type
        */
        PolyWrapper<ITypeInfo> GetReturnType()
        {
            return TypeID2<Tret>();
        }
        /*!
            Get the 'method' parameter types
            \return The 'method' parameter types
        */
        std::vector<PolyWrapper<ITypeInfo> > GetParamTypes()
        {
            return std::vector<PolyWrapper<ITypeInfo> >();
        }

        /*!
            Call function with vector<any> for arguements.
            \param info     The call information
            \param args     The method arguements as a vector<any>
            \return A default value
        */
        boost::any Call(MetaInfo &info, many args)
        {
            return Call(info, boost::any(NullValue));
        }
    };

}
#endif // DBGFNWRAP_HPP
