#include "meta.hpp"
#include "test.hpp"

#include <iostream>

#include "config.hpp"

using namespace std;
using namespace boost;

#include "tuple_util.hpp"

META_METHOD(foo_ctor, NO_RETURN, NO_PARAMS)
{
    cout << "foo created." << endl;
    MEM_INIT_VAL(string, bla, "Hello world!");
    return Nothing;
}

META_METHOD(foo_dtor, NO_RETURN, NO_PARAMS)
{
    cout << "foo destroyed." << endl;
    return Nothing;
}

META_METHOD(foo_bar, string, Q(tuple<int, string>))
{
    MEM(string, bla);
    string out=bla;
    for (int i=0; i<args.get<0>(); i++)
    {
        out+=args.get<1>();
    }
    return out;
}

META_METHOD(foo_set, NO_RETURN, tuple<string>)
{
    MEM(string, bla);
    bla=args.get<0>();
    return Nothing;
}

META_METHOD(foo_print, NO_RETURN, NO_PARAMS)
{
    MEM(string, bla);
    cout << bla << endl;
    return Nothing;
}

META_METHOD(foo_static, NO_RETURN, NO_PARAMS)
{
    cout << "Static method test." << endl;
    return Nothing;
}

template<typename T> void out_tuple(T tup)
{
    cout << tup << endl;
}

int main(int argc, char** argv)
{
    cout << __cplusplus << endl;
    meta::MetaClass foo("Foo");
    foo.AddStatic("static", meta::StdFn(foo_static));
    foo.AddMethod("ctor", meta::StdFn(foo_ctor));
    foo.AddMethod("dtor", meta::StdFn(foo_dtor));
    foo.AddMethod("bar", meta::StdFn(foo_bar));
    foo.AddMethod("set", meta::StdFn(foo_set));
    foo.AddMethod("print", meta::StdFn(foo_print));
    meta::MetaIface ifoo;
    ifoo.AddMethod(meta::IfaceMethod<NO_RETURN, NO_PARAMS>("static",true));
    ifoo.AddMethod(meta::IfaceMethod<string, tuple<int, string> >("bar"));

    TEST("Interface match", ifoo.IsMatch(foo));
    bool staticworked=false;
    try
    {
        foo["static"].Call();
        staticworked=true;
    }
    catch (std::exception &e)
    {
        staticworked=false;
    }
    TEST("Static call", staticworked);
    meta::MetaObject objfoo=meta::New(foo);
    TEST("Construction", ifoo.IsMatch(objfoo));
    TEST_R("Call with parameters/return",
           objfoo["bar"].Call<string>(MArgs(3, string("hi!"))), string("Hello world!hi!hi!hi!"));

    meta::MethodInfo barinfo=objfoo.GetMethodInfo("bar");
    TEST("Reflectivity",barinfo==foo.GetMethodInfo("bar"));
    TEST_R("Reflection return type", barinfo.GetReturnType()->Name(), TypeID<string>().Name());
    TEST_R("Reflection param types", barinfo.GetParamType(0)->Name(), TypeID<int>().Name());
    TEST_R("Call from reflection",
           barinfo.MakeCaller(objfoo).Call<string>(MArgs(3, string("ho!"))),
           string("Hello world!ho!ho!ho!"));
#if !defined(BOOST_NO_VARIADIC_TEMPLATES)
    TEST_R("Call by variadic template", objfoo["bar"].Call<string>(3, string("hi!")), string("Hello world!hi!hi!hi!"));
#endif

    /*string garb;
    getline(cin, garb);*/
    return 0;
}
