#include <stdio.h>
#include <string.h>

int comp, worst, best, calls;

int readfile(char *name, int a[])
{
    FILE *fp;
    int n = 0;
    fp = fopen(name, "r");
    while (fscanf(fp, "%d", &a[n]) == 1)
        n++;
    fclose(fp);
    return n;
}

void writefile(char *name, int a[], int n)
{
    FILE *fp;
    int i;
    fp = fopen(name, "w");
    for (i = 0; i < n; i++)
        fprintf(fp, "%d ", a[i]);
    fclose(fp);
}

void display(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int *p, int *q)
{
    int t;
    t = *p;
    *p = *q;
    *q = t;
}

int partition(int a[], int p, int r)
{
    int x, i, j;
    x = a[r];
    i = p - 1;
    for (j = p; j <= r - 1; j++)
    {
        comp++;
        if (a[j] <= x)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[r]);
    return i + 1;
}

void quicksort(int a[], int p, int r)
{
    int q, n;
    if (p < r)
    {
        n = r - p + 1;
        q = partition(a, p, r);
        calls++;
        if (q == p || q == r)
            worst++;
        else if ((q - p) <= n / 2 && (r - q) <= n / 2)
            best++;
        quicksort(a, p, q - 1);
        quicksort(a, q + 1, r);
    }
}

int main()
{
    int ch, n, a[500];
    char infile[30], outfile[30];

    while (1)
    {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &ch);

        if (ch == 4)
            break;
        if (ch == 1)
        {
            strcpy(infile, "inAsce.dat");
            strcpy(outfile, "outQuickAsce.dat");
        }
        else if (ch == 2)
        {
            strcpy(infile, "inDesc.dat");
            strcpy(outfile, "outQuickDesc.dat");
        }
        else if (ch == 3)
        {
            strcpy(infile, "inRand.dat");
            strcpy(outfile, "outQuickRand.dat");
        }
        else
            continue;

        n = readfile(infile, a);
        printf("Before Sorting: ");
        display(a, n);

        comp = 0;
        worst = 0;
        best = 0;
        calls = 0;
        quicksort(a, 0, n - 1);

        writefile(outfile, a, n);
        printf("After Sorting: ");
        display(a, n);
        printf("Number of Comparisons: %d\n", comp);
        if (worst * 2 >= calls)
            printf("Scenario: Worst-case\n");
        else
            printf("Scenario: Best-case\n");
    }
    return 0;
}
