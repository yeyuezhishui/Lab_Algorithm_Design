#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define filename "D:/Files/From_Vscode/C++/ex_algorithm/near_point_data.csv"

struct point
{
    int x;
    int y;
    int num; //点的编号
};           //点的数据类型

struct answer
{
    point m;
    point n;
    int distance;
};



point Data[N]; //原始数据
point P_x[N];  //按照x的升序排列的点
point P_y[N];  //按照y的升序排列的点

void Load_Data();
void Reduce_Sort(point *, int);            //归并排序,0按照x的升序，1按照y的升序
void quicksort_x(point *, int, int);       //按x升序归并排序
void quicksort_y(point *, int, int);       //按y升序归并排序
answer Closest_Pair_Rec(point *, point *,int); //递归主体
int dis_square(point,point);


answer Ans;

int main(void)
{
    int num_points = N;//初始时集合点的个数
    Load_Data();
    Reduce_Sort(P_x, 0);
    Reduce_Sort(P_y, 1);
    Ans = Closest_Pair_Rec(P_x, P_y,num_points);
    printf("the closest pair of points is (%d,%d) and (%d,%d) the distance of them is %.0f\n",Ans.m.x,Ans.m.y,Ans.n.x,Ans.n.y,sqrt(Ans.distance));
    return 0;
}

void Load_Data()
{
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("can not open the file\n");
    }
    int i = 0;
    for (; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i].x);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp, "%d", &Data[i].y);
        fseek(fp, 1L, SEEK_CUR);
        Data[i].num = i;
        P_x[i].x = Data[i].x;
        P_y[i].x = Data[i].x;
        P_x[i].y = Data[i].y;
        P_y[i].y = Data[i].y;
        P_x[i].num = i;
        P_y[i].num = i;
    }
    fclose(fp);
}

void Reduce_Sort(point *Data, int i)
{
    if (i == 0)
    {
        quicksort_x(Data, 0, N - 1);
    }
    else
        quicksort_y(Data, 0, N - 1);
}

void quicksort_x(point *Data, int low, int high)
{
    int i = low;
    int j = high;
    point temp = Data[i];
    if (low > high)
    {
        return;
    }
    while (i < j)
    {
        while ((Data[j].x >= temp.x) && (i < j))
        {
            j--;
        }
        Data[i] = Data[j];
        while ((Data[i].x <= temp.x) && (i < j))
        {
            i++;
        }
        Data[j] = Data[i];
    }
    Data[i] = temp;
    quicksort_x(Data, low, i - 1);
    quicksort_x(Data, j + 1, high);
}

void quicksort_y(point *Data, int low, int high)
{
    int i = low;
    int j = high;
    point temp = Data[i];
    if (low > high)
    {
        return;
    }
    while (i < j)
    {
        while ((Data[j].y >= temp.y) && (i < j))
        {
            j--;
        }
        Data[i] = Data[j];
        while ((Data[i].y <= temp.y) && (i < j))
        {
            i++;
        }
        Data[j] = Data[i];
    }
    Data[i] = temp;
    quicksort_y(Data, low, i - 1);
    quicksort_y(Data, j + 1, high);
}

answer Closest_Pair_Rec(point * P_x,point * P_y,int num)
{
    answer ans;
    int i;
    int j;
    int temp;
    int split = num/2;
    point Q_x[N];//左半边x的升序
    point Q_y[N];//左半边y的升序
    point R_x[N];//右半边y的升序
    point R_y[N]; //右半边y的降序
    point S[N];//边界周围区
    if(num<=3)//可以出结果的情况
    {
        ans.m = P_x[0];
        ans.n = P_x[1];
        ans.distance = dis_square(P_x[0],P_x[1]);
        for(i=0;i<num-1;i++)
        {
            for(j=i+1;j<num;j++)
            {
                if(dis_square(P_x[i],P_x[j])<ans.distance)
                {
                    ans.m = P_x[i];
                    ans.n = P_x[j];
                    ans.distance = dis_square(P_x[i],P_x[j]);
                }
            }
        }
    }
    else
    {
    //构造Q_x,Q_y,R_x,R_y
//构造左右集合
    int num_Q = 0;
    int num_R = 0;
    for(i = 0;i<split;i++)
    {
        Q_x[i] = P_x[i];
        num_Q++;
    }
    j = 0;
    for(i = split;i<num;i++)
    {
        if(P_x[i].x==P_x[split-1].x)//将分界线上的点全部归到左边
        {
            Q_x[i] = P_x[i];
            num_Q++;
        }
        else
        {
            R_x[j] = P_x[i];//分界线右侧的点归到一个集合
            j++;
            num_R++;
        }
    }
    int m = 0;
    int n = 0;
    for(i = 0;i<num;i++)
    {
        if(P_y[i].x<=Q_x[split-1].x)
        {
            Q_y[n] = P_y[i];
            n++;
        }
        else
        {
            R_y[m] = P_y[i];
            m++;
        }
    }

//递归求左右最优
    answer ans_Q;
    answer ans_R;
    ans_Q = Closest_Pair_Rec(Q_x,Q_y,num_Q);
    ans_R = Closest_Pair_Rec(R_x,R_y,num_R);

    if(ans_Q.distance<=ans_R.distance)
    {
        ans = ans_Q;
    }
    else
    {
        ans = ans_R;
    }
    }
//构造S
    int num_S = 0;
    for(i = 0;i<num;i++)
    {
        if(abs(P_x[i].x-P_x[split-1].x)<=ans.distance)
        {
            S[num_S] = P_x[i];
            num_S++;
        }
    }
//求解ans
    for(i = 0;i<num_S;i++)
    {
        for(j = 1;j<15;j++)
        {
            if(i+j>num_S-1)
            {
                break;
            }
            else
            {
                if(dis_square(S[i],S[i+j])<ans.distance)
                {
                    ans.m = S[i];
                    ans.n = S[i+j];
                    ans.distance = dis_square(S[i],S[j+1]);
                }
            }
        }
    }
    return ans;
}



int dis_square(point x,point y)
{
    return ((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}