#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node *list;
typedef struct node *position;

list MakeEmpty(list L)
{
    L = (list)malloc(sizeof(struct node));
    L->next = NULL;
    return L;
}

int isEmpty(list L)
{
    return L->next == NULL;
}

int isLast(position P, list L)
{
    return P->next == NULL;
}

position Find(int x, list L)
{
    position P;
    P = L->next;
    while (P != NULL && P->data != x)
    {
        P = P->next;
    }
    return P;
}

position FindPrevious(int x, list L)
{
    position P;
    P = L;
    while (P->next != NULL && P->next->data != x)
    {
        P = P->next;
    }
    return P;
}

void Delete(int x, list L)
{
    position P, TmpCell;
    P = FindPrevious(x, L);
    if (!isLast(P, L))
    {
        TmpCell = P->next;
        P->next = TmpCell->next;
        free(TmpCell);
    }
}

void Insert(int x, list L, position P)
{
    position TmpCell;
    TmpCell = (position)malloc(sizeof(struct node));
    if (TmpCell == NULL)
    {
        printf("Out of space!!!");
        exit(1);
    }
    TmpCell->data = x;
    TmpCell->next = P->next;
    P->next = TmpCell;
}

void DeleteList(list L)
{
    position P, Tmp;
    P = L->next;
    L->next = NULL;
    while (P != NULL)
    {
        Tmp = P->next;
        free(P);
        P = Tmp;
    }
}

void showList(list L)
{
    position P;
    P = L->next;
    while (P != NULL)
    {
        printf("%d ", P->data);
        P = P->next;
    }
    printf("\n");
}

int main()
{
    list L;
    position P;
    L = MakeEmpty(L);
    P = L;
    Insert(1, L, P);
    P = P->next;
    Insert(2, L, P);
    Insert(3, L, P);
    Insert(4, L, P);
    P = P->next;
    Insert(5, L, P);
    Find(3, L);
    Delete(3, L);

    showList(L);
    return 0;
}