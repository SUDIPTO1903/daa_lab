#include <stdio.h>

int main()
{
    FILE *fp;
    int n, i, j, a[100], visited[100];
    int count, dup, maxc, most;

    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    fp = fopen("input3.txt", "r");
    for (i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);
    fclose(fp);

    printf("The content of the array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    for (i = 0; i < n; i++)
        visited[i] = 0;

    dup = 0;
    maxc = 0;
    most = a[0];

    for (i = 0; i < n; i++)
    {
        if (visited[i] == 1)
            continue;
        count = 1;
        for (j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
            {
                count++;
                visited[j] = 1;
            }
        }
        if (count > 1)
            dup++;
        if (count > maxc)
        {
            maxc = count;
            most = a[i];
        }
    }

    printf("Total number of duplicate values = %d\n", dup);
    printf("The most repeating element in the array = %d\n", most);
    return 0;
}
