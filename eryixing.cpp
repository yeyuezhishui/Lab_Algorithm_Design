//基类的远近和访问的优先级有关
#include<iostream>
using namespace std;
class A
{
    int a;
    public:
        A(int m)
        {
            a = m;
        }
};
class B:public A
{
    public:
    int a;
    
    B(int n):A(n+1)
    {
        a = n;
    }
};
class C:public B
{
    public:
        C(int t):B(t)
        {

        }
};
int main(void)
{
    C c(1);
    cout<<c.a;
}