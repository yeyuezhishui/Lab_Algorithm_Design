#include <stdio.h>
#define filename_1 "D:/Files/From_Vscode/C++/xiaosuanfa/men.CSV"
#define filename_2 "D:/Files/From_Vscode/C++/xiaosuanfa/women.csv"
#define NUM_MAN 4
#define NUM_WOMAN 3

void Initial_table(void);
void Start_match(void);
void Print_Answer(void);
void Set_Num(void);
int Lowest_one(int which_woman,int *kick_one,int *position);

FILE * fp = NULL;
int Match_table[NUM_MAN + 1] = {0};
int Match_table_w[NUM_WOMAN + 1][NUM_MAN] = {0};
int men_table[NUM_MAN][NUM_WOMAN];
int how_many[NUM_MAN];
int women_table[NUM_WOMAN][NUM_MAN];

int main(void)
{
    Initial_table();
    Set_Num();
    Start_match();
    Print_Answer();
    return 0;
}

void Start_match()
{
    int i, j;
    int rank_1, rank_2;
    int kick_out_men;
    int kick_position;
    int loving_women;
    for (i = 1; i <= NUM_MAN; i++)
    {
        if (Match_table[i] == 0) //还没有找到医院的学生
        {
            for (j = 1; j <= NUM_WOMAN; j++) 
            {
                rank_1 = 0;
                rank_2 = 0;//计算两个匹配的优先级比较时使用
                loving_women = men_table[i-1][j-1];
                //先安排到医院列表中 不考虑学生的喜好
                if (Match_table_w[loving_women][0] > how_many[loving_women])
                {
                    Match_table[i] = loving_women;
                    Match_table_w[loving_women][how_many[loving_women]+1] = i;
                    how_many[loving_women]+=1;
                    break;
                }

                //当期的医院的实习生名额已经满了
                else
                {
                    //设计函数，求出当前优先级最低的那个学生的
                    rank_1 = Lowest_one(loving_women,&kick_out_men,&kick_position);
                    while (1)
                    {
                        if (women_table[j - 1][rank_2] != i)
                        {
                            rank_2++;
                        }
                        else
                            break;
                    }
                    if (rank_1 > rank_2)
                    {
                        Match_table[i] = j;
                        Match_table_w[loving_women][kick_position] = i;
                        Match_table[kick_out_men] = 0;
                        i = kick_out_men - 1;
                        break;
                    }
                    else
                        continue;
                }
            }
        }
        else continue;
    }

    for(i=1;i<=NUM_MAN;i++)
    {
        if(Match_table[i]==0)
        {
            printf("匹配失败");
        }
        else continue;
    }
}

void Initial_table()
{
    int i, j;
    fp = fopen(filename_1, "r");
    //读学生的数据
    for (i = 0; i < NUM_MAN; i++)
    {
        for (j = 0; j < NUM_WOMAN; j++)
        {
            fscanf(fp, "%d", &men_table[i][j]);
            fseek(fp, 1L, SEEK_CUR);
        }
    }
    fclose(fp);
    //读医院数据
    fp = fopen(filename_2, "r");
    for (i = 0; i < NUM_WOMAN; i++)
    {
        for (j = 0; j < NUM_MAN; j++)
        {
            fscanf(fp, "%d", &women_table[i][j]);
            fseek(fp, 1L, SEEK_CUR);
        }
    }
    fclose(fp);
}

void Print_Answer()
{
    int i;
    for(i = 1;i<=NUM_MAN;i++)
    {
        printf("the student(man) %d matches the hospital(womam) %d\n",i,Match_table[i]);
    }
}

void Set_Num()//设置每个医院的最大匹配数
{
    int i = 1;
    for(;i<=NUM_WOMAN;i++)
    {
        printf("how many student(men) the hospital(woman) %d wants to get: ",i);
        scanf("%d",&Match_table_w[i][0]);
    }
}

int Lowest_one(int which_woman,int *kick_one,int *position)//最low的值最大
{
    int i = 0;
    int Lowest_temp = 0;
    int rank_1;
    int first_men;
    for(i = 1;i<=how_many[which_woman];i++)
    {
        rank_1 = 0;
        while (1)
        {
            first_men = Match_table_w[which_woman][i];
            if (women_table[which_woman - 1][rank_1] != first_men)
            {
                rank_1++;
            }
            else
            {
                if(Lowest_temp<rank_1)
                {
                    Lowest_temp = rank_1;
                    *kick_one = first_men;
                    *position = i;
                }
                break;
            }
        }
    }
    return Lowest_temp;
}