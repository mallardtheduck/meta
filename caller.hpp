#ifndef CALLER_HPP_INCLUDED
#define CALLER_HPP_INCLUDED

#include <string>

#include "util.hpp"
#include "metacontext.hpp"
#include "metaclass.hpp"
#include "tuple_util.hpp"
#include "exceptions.hpp"

namespace meta
{
//! Method caller
/*!
    Class responsible for taking parameters and calling IFnWrap object.
*/
    class Caller
    {
    private:
        std::string _mname;
        PolyWrapper<IFnWrap> _fn;
        mutable MetaContext _context;
        MetaState &_state;
    public:
        /*!
            Constructor
            \param mname    The method name
            \param fn       IFnWrap object
            \param context  Method execution context
            \param state    Object state
        */
        Caller(const std::string &mname, PolyWrapper<IFnWrap> fn, MetaContext context, MetaState &state) :
                _mname(mname), _fn(fn), _context(context), _state(state) {}

        template<typename Tret, typename Tparam> Tret Call_Tuple(Tparam arg) const
        {
            if (!_fn().TypeCheck(TypeID<Tret>(),TypeID<Tparam>()))
            {
                throw Exceptions::TypeMismatch();
            }
            _context.ManyArgs=MkConvert(arg);
            MetaInfo ifo(_state, _context);
            if (TypeID<Tret>()==TypeID<NO_RETURN>())
            {
                _fn().Call(ifo, boost::any(arg));
                return Nothing;
            }
            else return boost::any_cast<Tret>(_fn().Call(ifo, boost::any(arg)));
        }        
                
        /*!
            Call operator for tuple
            \param arg  A tuple containing the method arguments
            \return     The method return value
        */
        template<typename Tret, typename Tparam> Tret operator()(Tparam arg) const
        {
            return Call_Tuple<Tret>(arg);
        }
        /*!
            Call method for tuple
            \param arg  A tuple containing the method arguements
            \return     The method return value
        */
        template<typename Tret, typename Tparam> Tret Call(Tparam arg) const
        {
            return Call_Tuple<Tret>(arg);
        }
        
        template<typename Tret> Tret Call_Many(many args) const
        {
            _context.ManyArgs=MkConvert(args);
            MetaInfo ifo(_state, _context);
            return boost::any_cast<Tret>(_fn().Call(ifo, args));
        }
        
        /*!
            Call operator for vector<any> (many).
            \param args     A vector<any> containing the method arguements
            \return         The method return value
        */
        template<typename Tret> Tret operator()(many args) const
        {
            return Call_Many<Tret>(args);
        }
        /*!
            Call method for vector<any> (many).
            \param args     A vector<any> containing the method arguements
            \return         The method return value
        */
        template<typename Tret> Tret Call(many args) const
        {
            return Call_Many<Tret>(args);
        }
        /*!
            Call operator for tuple with no return value
            \param arg      A typle containing the method arguements
        */
        template<typename Tparam> void operator()(Tparam arg) const
        {
            operator()<NO_RETURN>(arg);
        }
        /*!
            Call method for tuple with no return value
            \param arg      A typle containing the method arguements
        */
        template<typename Tparam> void Call(Tparam arg) const
        {
            operator()/*<Tparam>*/(arg);
        }
        /*!
            Call operator with no arguements
            \return     The method return value
        */
        template<typename Tret> Tret operator()() const
        {
            return operator()<Tret>(NullValue);
        }
        /*!
            Call method with not arguements
            \return     The method return value
        */
        template<typename Tret> Tret Call() const
        {
            return operator()<Tret>();
        }
        /*!
            Check the method type
            \param Tret     The return type
            \param Tparam   The type of the argements as a tuple
            \return         False if the type check fails, true if it passes or is unsupported by the IFnWrap
        */
        template<typename Tret, typename Tparam> bool TypeCheck()
        {
            return _fn().TypeCheck(TypeID<Tret>(),TypeID<Tparam>());
        }
        /*!
            Call operator vector<any> with any return
            \param args     The method arguements as a vector<any>
            \return         The method return value as an any
        */
        boost::any operator()(many args) const;
        /*!
            Call method vector<any> with any return
            \param args     The method arguements as a vector<any>
            \return         The method return value as an any
        */
        boost::any Call(many args) const;
        /*!
            Call operator with no arguements or return
        */
        void operator()() const;
        /*!
            Call method with no arguements or return
        */
        void Call() const;
        /*!
            Get the method name
            \return     The method name
        */
        
//#if !defined(BOOST_NO_VARIADIC_TEMPLATES)
                
        template<typename Tret, typename... Tparams> Tret Call_Variadic(Tparams... params){
            //return Call_Many<Tret>(variadic_to_many(params...));
            return Call_Tuple(boost::make_tuple(params...));
        }
        
        template<typename Tret, typename Tfirst,typename... Tparams> Tret operator()(Tfirst first, Tparams... params){
            return Call_Variadic<Tret>(first, params...);
        }

        template<typename Tret, typename Tfirst, typename... Tparams> Tret Call(Tfirst first, Tparams... params){
            return Call_Variadic<Tret>(first, params...);
        }

//#endif
        
        std::string GetName() const;
        /*!
            Get the method return type
            \return     The method return type
        */
        const ITypeInfo& GetReturnType() const;
        /*!
            Get the method parameter types
            \return     The method parameter types
        */
        std::vector<PolyWrapper<ITypeInfo> > GetParamTypes() const;

    };

}
#endif // CALLER_HPP_INCLUDED
