#include <stdio.h>

int main()
{
    int n, i, a[100], prefixSum[100];

    printf("Enter size of array: ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    prefixSum[0] = a[0];
    for (i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + a[i];

    printf("Input Array:\t");
    for (i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\n");

    printf("Output Array:\t");
    for (i = 0; i < n; i++)
        printf("%d\t", prefixSum[i]);
    printf("\n");
    return 0;
}
