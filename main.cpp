#include "metaclass.hpp"
#include "metaobject.hpp"
#include "new.hpp"
#include "stdfnwrap.hpp"
#include "dbgfnwrap.hpp"
#include "comp_util.hpp"
#include "iface.hpp"
#include "test.hpp"

#include <iostream>

using namespace std;
using namespace boost;

#include "tuple_util.hpp"

META_METHOD(foo_ctor, NO_RETURN, NO_PARAMS)
{
    cout << "foo created." << endl;
    MEM_INIT(string, bla);
    bla="Hello world!";
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
    MetaClass foo("Foo");
    foo.AddStatic("static", StdFn(foo_static));
    foo.AddMethod("ctor", StdFn(foo_ctor));
    foo.AddMethod("bar", StdFn(foo_bar));
    foo.AddMethod("set", StdFn(foo_set));
    foo.AddMethod("print", StdFn(foo_print));
    MetaIface ifoo;
    ifoo.AddMethod(IfaceMethod<NO_RETURN, NO_PARAMS>("static",true));
    ifoo.AddMethod(IfaceMethod<string, tuple<int, string> >("bar"));

    TEST("Interface match", ifoo.IsMatch(foo));
    bool staticworked=false;
    try{
        foo["static"].Call();
        staticworked=true;
    }catch(std::exception &e){
        staticworked=false;
    }
    TEST("Static call", staticworked);
    MetaObject objfoo=New(foo);
    TEST("Construction", ifoo.IsMatch(objfoo));
    TEST_R("Call with parameters/return",
        objfoo["bar"].Call<string>(make_tuple(3, string("hi!"))), string("Hello world!hi!hi!hi!"));

    MethodInfo barinfo=objfoo.GetMethodInfo("bar");
    TEST("Reflectivity",barinfo==foo.GetMethodInfo("bar"));
    TEST_R("Reflection return type", barinfo.GetReturnType()().Name(), TypeID<string>().Name());
    TEST_R("Reflection param types", barinfo.GetParamType(0)().Name(), TypeID<int>().Name());
    TEST_R("Call from reflection",
        barinfo.MakeCaller(objfoo).Call<string>(make_tuple(3, string("ho!"))),
        string("Hello world!ho!ho!ho!"));

/*    MetaClass dbgClass("DebugClass");
    dbgClass.AddMethod("ctor", DbgFnWrap<NO_RETURN, NO_PARAMS>());
    dbgClass.AddMethod("DoSomething", DbgFnWrap<int, tuple<int, int> >());
    MetaObject dbgObj=New(dbgClass);
    dbgObj["DoSomething"].Call<int>(make_tuple(1,2));

    out_tuple(make_tuple(3.76, "Hello world!", string("HAHA")));

    many m=tuple_to_many(make_tuple(4.5,(short)3,900000000,string("Hiya!"),'c', 0xfeedbabe, false, Nothing));
    for (size_t i=0; i<m.size(); i++)
    {
        cout << demangle(m[i].type().name()) << endl;
    }*/

    string garb;
    getline(cin, garb);
    return 0;
}
