#include <iostream>
using namespace std;

class A
{
private:
    int i;
public:
    A(int i);
    ~A();
};

A::A(int i)
{
    A::i = i;
    cout<<"A:i="<<A::i<<"\n";
}

A::~A()
{
    if(A::i)
    {
        cout<<"~A:i = "<<i<<"\n";
        i = 0;
    }
}

int main(void)
{
    A t(1);
    A &p = A(1); 
    // A &p=A(1); 马大头你的死妈的这样根本不行了
    return 0;
}