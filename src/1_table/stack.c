#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node *Stack;
typedef struct node *Position;

int isEmpty(Stack S)
{
    return S->next == NULL;
}

int Top(Stack S)
{
    if (!isEmpty(S))
    {
        return S->next->data;
    }
    printf("Empty stack\n");
    return 0;
}

void Pop(Stack S)
{
    Position FirstCell;
    if (isEmpty(S))
    {
        printf("Empty stack\n");
    }
    else
    {
        FirstCell = S->next;
        S->next = S->next->next;
        free(FirstCell);
    }
}

void Push(int x, Stack S)
{
    Position TmpCell;
    TmpCell = (Position)malloc(sizeof(struct node));
    if (TmpCell == NULL)
    {
        printf("Out of space\n");
        exit(1);
    }
    else
    {
        TmpCell->data = x;
        TmpCell->next = S->next;
        S->next = TmpCell;
    }
}

void DisposeStack(Stack S)
{
    Position P, Tmp;
    P = S->next;
    while (P != NULL)
    {
        Tmp = P->next;
        free(P);
        P = Tmp;
    }
    free(S);
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
    {
        printf("Must use CreateStack first\n");
        exit(1);
    }
    else
    {
        while (!isEmpty(S))
        {
            Pop(S);
        }
    }
}

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct node));
    if (S == NULL)
    {
        printf("Out of space\n");
        exit(1);
    }
    S->next = NULL;
    MakeEmpty(S);
    return S;
}

int main()
{
    Stack S;
    S = CreateStack();
    Push(1, S);
    Push(2, S);
    Push(3, S);
    printf("%d\n", Top(S));
    Pop(S);
    printf("%d\n", Top(S));
    Pop(S);
    printf("%d\n", Top(S));
    Pop(S);
    printf("%d\n", Top(S));
    DisposeStack(S);
    return 0;
}