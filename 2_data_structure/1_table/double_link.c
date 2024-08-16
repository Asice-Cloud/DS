#include <stdio.h>
#include <stdlib.h>

// double linked list
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

typedef struct node *List;
typedef struct node *Position;

void make_empty_double_list(List L)
{
    L = (List)malloc(sizeof(struct node));
    L->next = NULL;
    L->prev = NULL;
}

int is_empty_double_list(List L)
{
    return (L->next == NULL) && (L->prev == NULL);
}

int is_last_double_list(Position P, List L)
{
    return P->next == NULL;
}

Position Find_double_list(int x, List L)
{
    Position P;
    P = L->next;
    while (P != NULL && P->data != x)
    {
        P = P->next;
    }
    return P;
}

Position Find_previous_double_list(int x, List L)
{
    Position P;
    P = L;
    while (P->next != NULL && P->next->data != x)
    {
        P = P->next;
    }
    return P;
}

void Delete_double_list(int x, List L)
{
    Position P, TmpCell, TmpCell2;
    P = Find_previous_double_list(x, L);
    if (!is_last_double_list(P, L))
    {
        TmpCell = P->next;
        TmpCell2 = TmpCell->next;
        P->next = TmpCell->next;
        TmpCell2->prev = P;
        free(TmpCell);
    }
}

void Insert(int x, List L, Position P)
{
    Position TmpCell;
    TmpCell = (Position)malloc(sizeof(struct node));
    if (TmpCell == NULL)
    {
        printf("Out of space!!!");
    }
    TmpCell->data = x;
    TmpCell->next = P->next;
    P->next = TmpCell;
    TmpCell->prev = P;
    if (TmpCell->next != NULL)
    {
        TmpCell->next->prev = TmpCell;
    }
}

void show_all_double_list(List L)
{
    Position P;
    P = L->next;
    while (P != NULL)
    {
        printf("%d\n", P->data);
        P = P->next;
    }
}

int main()
{
    List L;
    make_empty_double_list(L);
    printf("Is the list empty? %d\n", is_empty_double_list(L));
    Insert(1, L, L);
    Insert(2, L, L);
    Insert(3, L, L->next);
    Insert(4, L, L->next);
    Insert(5, L, L->next);
    Delete_double_list(3, L);
    show_all_double_list(L);

    return 0;
}