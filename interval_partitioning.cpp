#include <stdio.h>
#include <stdlib.h>
#define N 10

struct lecture
{
    int id;//课程编号
    int begin;//课程开始时间
    int end;//课程结束时间
};

struct classroom
{
    int num;//教室编号
    struct classroom *next;//下一个教师地址
    int end;//当前教室的结束时间
    int lec_num;//当前的最晚结束时间
    int lec_id[N];//课程队列
};

void LoadData(); //加载数据
void Sort();//给课程按照开始时间的先后排序
void Start_Patition(classroom *);//开始匹配
void Print_Ans(classroom *);//打印结果

lecture lec_all[N];

int main(void)
{
    LoadData();

    //初始化教室队列
    classroom *first_one = (classroom *)malloc(sizeof(classroom));
    first_one->num = 1;
    first_one->end = 0;
    first_one->next = NULL;
    first_one->lec_num = 0;


    Sort();
    Start_Patition(first_one);
    Print_Ans(first_one);
    return 0;
}

void Sort()//冒泡排序
{
    int i;
    int k;
    lecture temp;
    for (i = 0; i < N - 1; i++)
    {
        for (k = 0; k < N - 1 - i; k++)
        {
            if (lec_all[k].begin > lec_all[k + 1].begin)
            {
                temp = lec_all[k];
                lec_all[k] = lec_all[k + 1];
                lec_all[k + 1] = temp;
            }
        }
    }
}

void LoadData()//按照图标给出的数据加载原始数据
{
    int i;
    for (i = 0; i < N; i++)
    {
        lec_all[i].id = i;
    }
    lec_all[0].begin = 0; //a
    lec_all[0].end = 5;
    lec_all[1].begin = 1; //b
    lec_all[1].end = 3;
    lec_all[2].begin = 1; //c
    lec_all[2].end = 5;
    lec_all[3].begin = 5; //d
    lec_all[3].end = 8;
    lec_all[4].begin = 4; //e
    lec_all[4].end = 10;
    lec_all[5].begin = 7; //f
    lec_all[5].end = 11;
    lec_all[6].begin = 8; //g
    lec_all[6].end = 12;
    lec_all[7].begin = 10; //h
    lec_all[7].end = 13;
    lec_all[8].begin = 11; //i
    lec_all[8].end = 15;
    lec_all[9].begin = 13; //j
    lec_all[9].end = 15;
}

void Start_Patition(classroom *first_one)
{
    int i;
    classroom* pre = NULL;
    for (i = 0; i < N; i++)
    { 
        classroom *current = first_one;
        while (current != NULL)
        {  
            //判断队首课程的开始时间是否在当前教室结束时间之后
            if (lec_all[i].begin >= current->end)
            {
                current->lec_num += 1;
                current->lec_id[current->lec_num-1] = lec_all[i].id;
                current->end = lec_all[i].end;
                break;
            }
            else
            //不能匹配该教室 指针移向下一个教室
            {
                pre = current;
                current = current->next;
            }
        }
        //如果当前教室队列里没有可以匹配的教室 在教室队列队尾新建教室节点
        if (current == NULL)
        {
            pre->next = (classroom *)malloc(sizeof(classroom));
            pre->next->end = lec_all[i].end;
            pre->next->lec_num = 1;
            pre->next->lec_id[pre->next->lec_num - 1] = lec_all[i].id;
            pre->next->next = NULL;
            pre->next->num = pre->num + 1;
        }
        else
        {
            continue;
        }
    }
}

void Print_Ans(classroom *first_one)
{
    classroom * current = first_one;
    int * current_lec = NULL;
    int i = 0;
    while(current)
    {
        current_lec = current->lec_id;
        for(i=0;i<current->lec_num;i++)
        {
            printf("class %d will be held in classroom %d \n",current_lec[i],current->num);
        }
        current=current->next;
    }
}