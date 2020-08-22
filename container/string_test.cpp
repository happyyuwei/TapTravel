#include <iostream>
#include "string.h"
#include <algorithm>
#include <vector>

TAP::String get()
{
    TAP::String str("hello");
    return str;
}

int main()
{

    TAP::String str1 = "helelloell my dear";
    TAP::String str2 = "my";
    TAP::String str3 = "dear";
    TAP::String str4;
     std::cout << str4.size() << std::endl;

    // std::cout << (str1 + " " + str2 + " " + str3) << std::endl;
    // std::cout << (str1 + " " + str2 + " " + str3) << std::endl;

    // std::cout << str1.find(str2) << std::endl;

    // TAP::String &s = str1.subString(1).subString(2);

    // std::cout << str1 << std::endl;
    // std::cout << str1.replace("my", "yes") << std::endl;

    TAP::String str5 = "a-b-c-d-e-f";
    std::vector<TAP::String> v = str5.split("-");
    std::cout << "display" << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }

    //123456
    //34

    // 23

    return 0;
}