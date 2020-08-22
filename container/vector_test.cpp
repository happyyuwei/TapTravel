#include <iostream>
#include "vector.h"
#include <algorithm>
#include <vector>
#include "string.h"

TAP::Vector<int> get()
{
    TAP::Vector<int> v1;
    for (int i = 100; i < 117; i++)
    {
        v1.push_back(i);
    }
    return v1;
}

int main()
{

    // TAP::Vector<int> v2 = get();
    // int *a;
    // std::cout << v2.empty() << std::endl;
    // v2.push_back(1000);
    // std::cout << "after v2 copy display" << std::endl;
    // std::cout << v2<< std::endl;
    // std::cout<<v2.pop_back()<<std::endl;

    // v2.clear();
    // std::cout << v2 << std::endl;
    // v2.push_back(1000);
    // v2.push_back(100);
    // v2.push_back(10);
    // std::cout << v2 << std::endl;

    // std::sort(v2.begin(), v2.end());

    // std::cout<<v2<<std::endl;

    // for(TAP::Vector<int>::iterator i=v2.begin(); i!=v2.end();i++){
    //     std::cout<<"out by iter: "<<*i<<std::endl;
    // }

    // char a[]="hello my dear";
    // TAP::Vector<char> v2(a, a+6);
    std::vector<TAP::String> *s = new std::vector<TAP::String>();

    std::cout << s << std::endl;

    return 0;
}