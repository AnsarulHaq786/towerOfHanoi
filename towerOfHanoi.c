#include<stdio.h>
#include <stdlib.h>
int step=0,i;
struct Rod
{
    int n;
    int *disc;
    int top;
} *A, *B, *C;
struct Rod *createRod(int);
void initialState(struct Rod *, struct Rod *, struct Rod *, int);
int pop(struct Rod *);
void push(struct Rod *, int);
void display(struct Rod *, struct Rod *, struct Rod *, int);
void TOH(struct Rod *, struct Rod *, struct Rod *, int);
int main()
{
    int n;
    printf("Enter no of disc: ");
    scanf("%d",&n);
    A = createRod(n);
    B = createRod(n);
    C = createRod(n);
    initialState(A, B, C, n);
    TOH(A, C, B, n);
    free(A->disc);
    free(B->disc);
    free(C->disc);
    free(A);
    free(B);
    free(C);
    return 0;
}
struct Rod *createRod(int n)
{
    struct Rod *rod = (struct Rod *)malloc(sizeof(struct Rod));
    rod->n = n;
    rod->disc = (int *)calloc(n, sizeof(int));
    rod->top = -1;
    return rod;
}
void initialState(struct Rod *A, struct Rod *B, struct Rod *C, int n)
{
    for (i=n; i>0; i--)
    {
        push(A, i);
    }
    display(A, B, C, A->n);
}
int pop(struct Rod *rod)
{
    int from;
    from=rod->disc[rod->top];
    rod->top--;
    return from;
}
void push(struct Rod *rod, int from)
{
    rod->top++;
    rod->disc[rod->top] = from;
}
void display(struct Rod *A, struct Rod *B, struct Rod *C, int n)
{
    printf("Step:%d\n", step);
    step++;
    for (i=n-1; i>=0; i--)
    {
        printf("%c\t", (i <= A->top) ? '0' + A->disc[i] : ' ');
        printf("%c\t", (i <= B->top) ? '0' + B->disc[i] : ' ');
        printf("%c\t", (i <= C->top) ? '0' + C->disc[i] : ' ');
        printf("\n");
    }
    printf("A\tB\tC\n");
}
void TOH(struct Rod *source, struct Rod *sink, struct Rod *auxiliary, int n)
{
    if (n==1)
    {
        int from;
        from = pop(source);
        push(sink,from);
        display(A, B, C, source->n);
        return;
    }
    TOH(source, auxiliary, sink, n-1);
    TOH(source, sink, auxiliary, 1);
    TOH(auxiliary, sink, source, n-1);
}
