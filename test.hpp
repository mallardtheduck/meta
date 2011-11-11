#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <string>
#include <iostream>

#define TEST(d, t) Test(__FILE__, __LINE__, d, t)
#define TEST_R(d, t, r) TestR(__FILE__, __LINE__, d, t, r);

inline void Test(std::string file, int line, std::string desc, bool test)
{
    std::cout << "Test: '" << desc << "' Result: "<< (test?"Pass":"FAIL") << std::endl;
    if (!test) std::cout << "*** FAILED TEST AT: " << file << ":" << line << std::endl;
}

template<typename T> void TestR(std::string file, int line, std::string desc, T test, T expresult)
{
    std::cout << "Test: '" << desc << "' Result: "<< (test==expresult?"Pass":"FAIL") << std::endl;
    if (test!=expresult)
    {
        std::cout << "*** FAILED TEST AT: " << file << ":" << line << std::endl;
        std::cout << "*** Expected: '" << expresult << "' Got: '" << test << "'" << std::endl;
    }
}

#endif // TEST_HPP_INCLUDED
