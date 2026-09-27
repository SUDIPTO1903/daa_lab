#include <stdio.h>

int main()
{
    FILE *fp;
    int n, i, j, t, a[100], s2, l2;

    fp = fopen("input1.txt", "r");
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);
    fclose(fp);

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    s2 = a[1];
    for (i = 1; i < n; i++)
    {
        if (a[i] != a[0])
        {
            s2 = a[i];
            break;
        }
    }

    l2 = a[n - 2];
    for (i = n - 2; i >= 0; i--)
    {
        if (a[i] != a[n - 1])
        {
            l2 = a[i];
            break;
        }
    }

    printf("Second smallest = %d\n", s2);
    printf("Second largest = %d\n", l2);
    return 0;
}
