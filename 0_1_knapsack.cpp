#include <iostream>
using namespace std;
#define N 4//物品个数
#define W 50//背包的容量
 
//物品数据结构
struct GOODS
{
    int value;  //价值
    int weight; //重量
};
 
//初始物品信息
GOODS goods[N+1]={{0,0},{60,10},{100,20},{120,30},{70,35}};
int Ans[N+1][W+1];//选择表
 
int max_value();
 
int main()
{
    int maxvalue = max_value();
    cout<<"The max value is: ";
    cout<<maxvalue<<endl;
    int remainspace = W;
    //输出所选择的物品列表
    for(int i=N; i>=1; i--)
    {
        if (remainspace >= goods[i].weight)
        {
             if ((Ans[i][remainspace]-Ans[i-1][remainspace-goods[i].weight]==goods[i].value))
             {
                 cout  << i << " is in the bag" << endl;
                 remainspace = remainspace - goods[i].weight;
             }
        }
    }
    return 0;
}
int max_value()
{
    int w;
    int i;
    for(w = 0;w<=W;w++)
    {
        Ans[0][w] = 0;
    }
    for(i = 1;i<=N;i++)
    {
        Ans[i][0] = 0;
        for(w = 1;w<=W;w++)
        {
            if(goods[i].weight>w)
            {
                Ans[i][w] = Ans[i-1][w];
            }
            else
            {
                if(Ans[i-1][w]>Ans[i-1][w-goods[i].weight]+goods[i].value)
                {
                    Ans[i][w] = Ans[i-1][w];
                }
                else
                {
                    Ans[i][w] = Ans[i-1][w-goods[i].weight]+goods[i].value;
                }
            }
        }
    }
    return Ans[N][W];
}