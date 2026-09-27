#include <stdio.h>

void EXCHANGE(int *p, int *q)
{
    int t;
    t = *p;
    *p = *q;
    *q = t;
}

void ROTATE_RIGHT(int *p1, int p2)
{
    int i;
    for (i = p2 - 1; i > 0; i--)
        EXCHANGE(&p1[i], &p1[i - 1]);
}

int main()
{
    int n, i, a[100];

    printf("Enter an array A of size N (9): ");
    n = 9;
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Before ROTATE:\t");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    ROTATE_RIGHT(a, 5);

    printf("After   ROTATE:\t");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
