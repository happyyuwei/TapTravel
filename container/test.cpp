#include <iostream>
//-fno-elide-constructors

template <class T>
class V
{
};

template <class T>
class S : public V<char>
{
public:
    V<S> split()
    {
        V<S> v;
        return v;
    }
};

int main()
{
    
}