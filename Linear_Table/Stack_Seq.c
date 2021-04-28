#include<stdio.h>
#define MAXSIZE 1000

struct Stack
{
    int data[MAXSIZE];
    int top;
}S;

int Check_Valid(int seq[], int M, int N);
int main()
{
    //input
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int data[K][N];
    for(int i = 0;i<K;i++)
    {
        for(int j = 0;j < N;j++)
        {
            scanf("%d", &data[i][j]);
        }
    }
    //check in order
    for(int i = 0;i < K;i++)
    {
        int res = Check_Valid(data[i], M, N);
        printf("%s\n", res == 1 ? "YES" : "NO");
    }
    return 0;
}

int Check_Valid(int seq[], int M, int N)
{
    int res = 1;
    int flag = 1, cur = 0;
    S.top = -1;
    for(int i = 0;i < N;i++)
    {
        S.data[++S.top] = i+1;
        //判断是否溢出
        if(S.top + 1 > M) flag = 0;
        //判断是否非法
        if(flag == 0 || seq[cur] < S.data[S.top])
        {
            res = 0;
            break;
        }
        while(seq[cur] == S.data[S.top] && S.top != -1)
        {
            S.top--;
            cur++;
        }
    }
    if(cur != N) res = 0;
    return res;
}