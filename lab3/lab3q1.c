#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

int comp;

#ifdef _WIN32
long long getns()
{
    LARGE_INTEGER f, t;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t);
    return (t.QuadPart * 1000000000LL) / f.QuadPart;
}
#else
long long getns()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
#endif

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

void merge(int a[], int l, int m, int r)
{
    int n1, n2, i, j, k;
    int L[500], R[500];
    n1 = m - l + 1;
    n2 = r - m;
    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        comp++;
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
}

void mergesort(int a[], int l, int r)
{
    int m;
    if (l < r)
    {
        m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main()
{
    int ch, n, a[500], i;
    long long t1, t2;
    char infile[30], outfile[30];

    while (1)
    {
        printf("MAIN MENU (MERGE SORT)\n");
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
            strcpy(outfile, "outMergeAsce.dat");
        }
        else if (ch == 2)
        {
            strcpy(infile, "inDesc.dat");
            strcpy(outfile, "outMergeDesc.dat");
        }
        else if (ch == 3)
        {
            strcpy(infile, "inRand.dat");
            strcpy(outfile, "outMergeRand.dat");
        }
        else
            continue;

        n = readfile(infile, a);
        printf("Before Sorting: ");
        display(a, n);

        comp = 0;
        t1 = getns();
        mergesort(a, 0, n - 1);
        t2 = getns();

        writefile(outfile, a, n);
        printf("After Sorting: ");
        display(a, n);
        printf("Number of Comparisons: %d\n", comp);
        printf("Execution Time: %lld\n", t2 - t1);
    }
    return 0;
}
