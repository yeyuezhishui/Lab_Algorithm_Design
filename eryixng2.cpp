#include<iostream>
using namespace std;
struct A
{
    public:
        int a;
        A(int m)
        {
            a = m;
        }
};
struct B: virtual A
// struct B: A  这种继承方式会带来二义性
{
    public:
    B(int n):A(n)
    {
    }
};
struct C:virtual A
{
    public:
        C(int t):A(t)
        {

        }
};
struct D:B,C
{
    public:
    D(int x):A(1),B(x+1),C(x+2)
    {}
};
int main(void)
{
    D d(1);
    cout<<d.a;
}