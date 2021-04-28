#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100000
struct Node
{
    int data;
    int next;
}List[MAXSIZE];

int Reverse_K(int start_idx, int K);
int main()
{
    int start_idx, N, K;
    scanf("%d %d %d", &start_idx, &N, &K);
    int idx, data, next;
    for(int i = 0;i < N;i++)
    {
        scanf("%d %d %d", &idx, &data, &next);
        List[idx].data = data;
        List[idx].next = next;
    }
    int real_num = 0;
    for(int i = start_idx;i != -1;i = List[i].next) real_num++;
    N = real_num;
    if(K >= 2 && N >= K)
    {
        int segment_start_idx = start_idx;
        start_idx = Reverse_K(start_idx, K);
        N -= K; 
        while(N >= K)
        {
            int former_idx = segment_start_idx;
            segment_start_idx = List[segment_start_idx].next;
            List[former_idx].next = Reverse_K(segment_start_idx, K);
            N -= K;
        }
    }
    int tmp = start_idx;
    while(tmp != -1)
    {
        if(List[tmp].next != -1)
        {
            printf("%05d %d %05d\n", tmp, List[tmp].data, List[tmp].next);
        }
        else printf("%05d %d %d\n", tmp, List[tmp].data, List[tmp].next);
        tmp = List[tmp].next;
    }
}

int Reverse_K(int start_idx, int K)
{
    int new = start_idx; 
    int old = List[start_idx].next;
    int post = List[old].next;
    for(int i = 0;i < K - 1;i++)
    {
        List[old].next = new;
        new = old;
        old = post;
        if(post != -1) post = List[post].next;
    }
    List[start_idx].next = old;
    return new;
}