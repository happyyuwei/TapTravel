#include <iostream>
//-fno-elide-constructors

class A
{
public:
    A()
    {
        std::cout << "create\n";
    }
    ~A()
    {
        std::cout << "delete\n";
    }
};

void init()
{
    A a;

    A b;
    b=a;
    std::cout << "before return\n";
}
int main()
{
    init();
    std::cout << "after init\n";
}