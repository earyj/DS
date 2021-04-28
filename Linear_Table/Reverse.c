#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int addr;
    int data;
    int next_addr;
    struct Node *next;
};
typedef struct Node *List;

List Read_List(int N, int start_addr);
void Attach(int addr, int data, int next_addr, List *tail);
void Reverse(List *L, int K, int N);
List Reverse_K(List first_ptr, int K);
void PrintOut(List L);
int main()
{
    int K, start_addr, N;
    scanf("%d %d %d", &start_addr, &N, &K);
    //读入数组并按地址排序
    List L = Read_List(N, start_addr);
    //逆序
    Reverse(&L, K, N);
    //输出
    PrintOut(L);
}

List Read_List(int N, int start_addr)
{
    List L = (List)malloc(sizeof(struct Node));
    L->next = NULL;
    struct Node *tail = L, *tmp;
    int addr, data, next_addr;
    int k = N;
    while(k--)
    {
        scanf("%d", &addr);
        scanf("%d", &data);
        scanf("%d", &next_addr);
        Attach(addr, data, next_addr, &tail);
    }
    tmp = L;
    L = L->next;
    free(tmp);
    //调整链表顺序
    struct Node **ptr_list = (List *)malloc(sizeof(struct Node*)*N);
    addr = start_addr;
    for(int i = 0;i < N;i++)
    {
        tmp = L;
        while(tmp)
        {
            if(tmp->addr == addr)
            {
                ptr_list[i] = tmp;
                addr = tmp->next_addr;
                break;
            }
            tmp = tmp->next;
        }
    }
    for(int i = 0;i <= N-2;i++)
    {
        ptr_list[i]->next = ptr_list[i+1];
    }
    ptr_list[N-1]->next = NULL;
    L = ptr_list[0];
    return L;
}

void Attach(int addr, int data, int next_addr, List *tail)
{
    List tmp = (List)malloc(sizeof(struct Node));
    tmp->addr = addr;
    tmp->data = data;
    tmp->next_addr = next_addr;
    tmp->next = NULL;
    (*tail)->next = tmp;
    (*tail) = tmp;
}

void Reverse(List *L, int K, int N)
{
    if(N < K) return;
    List tmp = *L, former = *L;
    *L = Reverse_K(tmp, K);
    N -= K;
    tmp = tmp->next;
    while(N >= K)
    {
        former->next = Reverse_K(tmp, K);
        former = tmp;
        tmp = (tmp)->next;
        N -= K;
    }
}

List Reverse_K(List first_ptr, int K)
{
    if(K <= 1) return first_ptr;
    struct Node *new = first_ptr, *old = first_ptr->next, *post = old->next;
    K -= 1;
    int tmp;
    while(K--)
    {
        old->next = new;
        old->next_addr = new->addr;
        new = old;
        old = post;
        post = post->next;
    }
    first_ptr->next = old;
    first_ptr->next_addr = old->addr;
    return new;
}

void PrintOut(List L)
{
    while(L)
    {
        if(L->next_addr == -1)
        {
            printf("%5d %d %d", L->addr, L->data, L->next_addr);
        }
        else
        {
            printf("%05d %d %05d\n", L->addr, L->data, L->next_addr);
        }
        L = L->next;
    }
}