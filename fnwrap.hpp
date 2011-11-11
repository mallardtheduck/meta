#ifndef FNWRAP_HPP
#define FNWRAP_HPP

#include <iostream>
#include <typeinfo>
#include <boost/any.hpp>
#include <boost/tuple/tuple_io.hpp>

#include "util.hpp"
#include "polywrapper.hpp"
#include "metacontext.hpp"

#include "tuple_util.hpp"

namespace meta
{

    class MetaInfo;

    //! Interface for "function wrappers"
    /*!
        An interface for classes that wrap methods or functions.
        Includes the calling interface.
    */
    class IFnWrap
    {
    protected:
        bool _static;
    public:
        /*!
            Constructor
        */
        IFnWrap() : _static(false) {}
        /*!
            Check the method types
            \param retType      The return type to test
            \param paramType    The parameter types to test (as a tuple type)
            \return false if the typecheck fails, true if it succeeds or is not supported
        */
        virtual bool TypeCheck(const ITypeInfo &retType, const ITypeInfo &paramType)=0;
        /*!
            Call the method with tuple arguements
            \param info     The call information
            \param args     The method arguements as a tuple wrapped in an any
            \return The method return value wrapped in an any
        */
        virtual boost::any Call(MetaInfo &info, boost::any args)=0;
        /*!
            Call the method with vector<any> arguements
            \param info     The call information
            \param args     The method arguements as a vector<any>
            \return The method return value wrapped in any any
        */
        virtual boost::any Call(MetaInfo &info, many args)=0;

        /*!
            Get the method return type
            \return The method return type
        */
        virtual PolyWrapper<ITypeInfo> GetReturnType()=0;
        /*!
            Get the method parameter types
            \return The method parameter types
        */
        virtual std::vector<PolyWrapper<ITypeInfo> > GetParamTypes()=0;

        /*!
            Is the method static? (implemented in interface)
            \return true if the method is static, false otherwise
        */
        virtual bool IsStatic()
        {
            return _static;
        }
        /*!
            Set the method static or not (implemented in interface)
            \param s    true to make the method static, false to make it obeject-dependent
        */
        virtual void SetStatic(bool s)
        {
            _static=s;
        }
        /*!
            Empty virtual destructor
        */
        virtual ~IFnWrap(){}
    };
}
#endif // FNWRAP_HPP
