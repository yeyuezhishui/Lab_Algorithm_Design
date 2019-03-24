#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 20 //字符串X的最大长度
#define N 20 //字符串Y的最大长度
#define SPACE 2
#define WRONG 6

void Load_Data(int *,int *);//输入待比较字符串
void Init_table(int,int);//初始化路径表
void Start_Compare(int,int);//比较主体
void TraceBack_Ans(int,int);

enum Movement {left,behind,direct,stay};

struct ans_table
{
    int ans;
    Movement mov;
};

char X[M+1];//字符串X
char Y[N+1];//字符串Y
ans_table A[M][N];//匹配表
char Ans_X[2*M];
char Ans_Y[2*N];

int main(void)
{
    int m,n;//字符串XY的实际长度包括字符串结尾
    Load_Data(&m,&n);
    Init_table(m,n);
    Start_Compare(m,n);
    TraceBack_Ans(m,n);
    return 0;
}


void Load_Data(int *m,int *n)
{
    printf("请输入字符串X:");
    scanf("%s",&X);
    *m = strlen(X);
    printf("请输入字符串Y:");
    scanf("%s",&Y);
    *n = strlen(Y);
}

void Init_table(int m,int n)
{
    int i;
    int j;
    for(i =0;i<=m;i++)
    {
        A[i][0].ans = i*SPACE;
        A[i][0].mov = left;
    }
    for(j = 0;j<=n;j++)
    {
        A[0][j].ans = j*SPACE;
        A[0][j].mov = behind;
    }
    A[0][0].mov = stay;
}

void Start_Compare(int m,int n)
{
    int i;
    int j;
    int cho_1;//匹配代价+OPT（i-1；j-1）
    int cho_2;//SPACE + OPT(i-1,j)
    int cho_3;//SPACE + OPT(j,i-1)
    int min;
    int pos_x = 0;
    int pos_y = 0;
    for(i = 1;i<m+1;i++)
    {
        for(j=1;j<n+1;j++)
        {
            if(X[i-1]==Y[j-1])
            {
                cho_1 = A[i-1][j-1].ans;
            }
            else cho_1 = A[i-1][j-1].ans+WRONG;
            cho_2 = A[i-1][j].ans+SPACE;
            cho_3 = A[i][j-1].ans+SPACE;
            min = cho_1;
            if(min >= cho_2)
            {
                min = cho_2;
            }
            if(min >= cho_3)
            {
                min = cho_3;
            }
            if(min==cho_1)
            {
                A[i][j].mov = direct;
            }
            else if(min == cho_2)
            {
                A[i][j].mov = left;
            }

            else if(min == cho_3)
            {
                A[i][j].mov = behind;
            }
            A[i][j].ans = min;
        }
    }
}


void TraceBack_Ans(int m,int n)
{
    printf("the best alighment cost %d\n",A[m][n]);
    Movement back_mov;
    Movement forward_mov;
    Movement Mov_stack[M*M];
    int i =0 ;
    int j = 0;
    int pos_x = 0;
    int pos_y = 0;

    back_mov = A[m][n].mov;
    while(true)
    {
        Mov_stack[i] = back_mov;
        switch (back_mov)
        {
            case left:
                m = m-1;
                break;
            case behind:
                n = n-1;
                break;
            case direct:
                n = n-1;
                m = m-1;
                break;
            default:
                break;
        }
        if(m==0&&n==0)
        {
            break;
        }
        back_mov = A[m][n].mov;
        i++;
    }
    for(;i>=0;i--)
    {
        forward_mov = Mov_stack[i];
        switch (forward_mov)
        {
            case left:
                Ans_Y[j] = '-';
                Ans_X[j] = X[pos_x];
                pos_x++;
                j++;
                break;
            case behind:
                Ans_Y[j] = Y[pos_y];
                Ans_X[j] = '-';
                pos_y++;
                j++;
                break;
            case direct:
                Ans_X[j] = X[pos_x];
                Ans_Y[j] = Y[pos_y];
                pos_x++;
                pos_y++;
                j++;
                break;
            case stay:
                break;
            default:
                break;
        }
    }
    printf("the best Alighment is:\n%s\n%s",Ans_X,Ans_Y);
}