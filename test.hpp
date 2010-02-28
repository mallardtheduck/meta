#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <string>
#include <iostream>
using namespace std;

#define TEST(d, t) Test(__FILE__, __LINE__, d, t)
#define TEST_R(d, t, r) TestR(__FILE__, __LINE__, d, t, r);

inline void Test(string file, int line, string desc, bool test){
    cout << "Test: " << desc << " Result: "<< (test?"Pass":"FAIL") << endl;
    if(!test) cout << "*** FAILED TEST AT: " << file << ":" << line << endl;
}

template<typename T> void TestR(string file, int line, string desc, T test, T expresult){
    cout << "Test: " << desc << " Result: "<< (test==expresult?"Pass":"FAIL") << endl;
    if(test!=expresult){
        cout << "*** FAILED TEST AT: " << file << ":" << line << endl;
        cout << "*** Expected: " << expresult << " Got: " << test << endl;
    }
}

#endif // TEST_HPP_INCLUDED
