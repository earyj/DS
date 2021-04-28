#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef struct Node* Polynomial;
struct Node
{
    ElementType coef;
    ElementType expo;
    struct Node* next;
};


Polynomial Read();
void Attach(ElementType coef, ElementType expo, Polynomial *tail);
Polynomial Add(Polynomial l1, Polynomial l2);
Polynomial Multi(Polynomial l1, Polynomial l2);
void PrintOut(Polynomial P);
int main()
{
    //读取输入
    Polynomial P1 = Read();
    Polynomial P2 = Read();
    //计算乘积多项式
    Polynomial PM = Multi(P1, P2);
    //计算和多项式
    Polynomial PA = Add(P1, P2);
    //输出
    PrintOut(PM);
    PrintOut(PA);
}

Polynomial Read()
{
    Polynomial L = (Polynomial)malloc(sizeof(struct Node));
    L->next = NULL;
    struct Node *tail = L, *tmp;
    int len;
    scanf("%d", &len);
    while(len--)
    {
        ElementType coef, expo;
        scanf("%d %d", &(coef), &(expo));
        Attach(coef, expo, &tail);
    }
    tmp = L;
    L = L->next;
    free(tmp);
    return L;
}

void Attach(ElementType coef, ElementType expo, Polynomial *tail)
{
    Polynomial tmp = (Polynomial)malloc(sizeof(struct Node));
    tmp->coef = coef;
    tmp->expo = expo;
    tmp->next = NULL;
    (*tail)->next = tmp;
    (*tail) = tmp;
}

Polynomial Add(Polynomial l1, Polynomial l2)
{
    Polynomial res = (Polynomial)malloc(sizeof(struct Node));
    Polynomial tail = res, tmp;
    res->next = NULL;
    while(l1 && l2)
    {
        if(l1->expo > l2->expo)
        {
            Attach(l1->coef, l1->expo, &tail);
            l1 = l1->next;
        }
        else if(l1->expo < l2->expo)
        {
            Attach(l2->coef, l2->expo, &tail);
            l2 = l2->next;
        }
        else
        {
            if(l1->coef + l2->coef)
            {
                Attach(l1->coef + l2->coef, l1->expo, &tail);
            }
            l1 = l1->next;
            l2 = l2->next;
        }
    }
    for(;l1;l1 = l1->next) Attach(l1->coef, l1->expo, &tail);
    for(;l2;l2 = l2->next) Attach(l2->coef, l2->expo, &tail);
    tmp = res;
    res = res->next;
    free(tmp);
    return res;
    
}

Polynomial Multi(Polynomial l1, Polynomial l2)
{
    if(!l1 || !l2) return NULL;
    Polynomial t1 = l1;
    Polynomial t2 = l2;
    Polynomial res = (Polynomial) malloc(sizeof(struct Node));
    Polynomial tail = res, tmp, tmp1;
    while(t2)
    {
        Attach(t1->coef * t2->coef, t1->expo + t2->expo, &tail);
        t2 = t2->next;
    }
    t1 = l1->next;
    while(t1)
    {
        t2 = l2;
        while(t2)
        {
            ElementType expo = t1->expo + t2->expo;
            ElementType coef = t1->coef * t2->coef;
            tmp = res;
            while(tmp->next && (tmp->next)->expo > expo)
            {
                tmp = tmp->next;
            }
            if(tmp->next && (tmp->next)->expo == expo)
            {
                if(coef + (tmp->next)->coef)
                {
                    (tmp->next)->coef += coef;
                }
                else
                {
                    tmp1 = tmp->next;
                    tmp->next = tmp1->next;
                    free(tmp1);
                }
            }
            else
            {
                tmp1 = tmp->next;
                Attach(coef, expo, &tmp);
                tmp->next = tmp1;
            }
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    tmp = res;
    res = res->next;
    free(tmp);
    return res;
}

void PrintOut(Polynomial P)
{
    if(!P)
    {
        printf("0 0\n");
        return;
    }
    while(P)
    {
        printf("%d %d", P->coef, P->expo);
        if(P->next != NULL)
        {
            printf(" ");
        }
        P = P->next;
    }
    printf("\n");
}