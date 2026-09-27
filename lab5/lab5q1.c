#include <stdio.h>

struct ITEM
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
    float amount;
};

void swap(struct ITEM *a, struct ITEM *b)
{
    struct ITEM t;
    t = *a;
    *a = *b;
    *b = t;
}

void heapify(struct ITEM a[], int n, int i)
{
    int largest, l, r;
    largest = i;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < n && a[l].profit_weight_ratio > a[largest].profit_weight_ratio)
        largest = l;
    if (r < n && a[r].profit_weight_ratio > a[largest].profit_weight_ratio)
        largest = r;
    if (largest != i)
    {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

void heapsort(struct ITEM a[], int n)
{
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

int main()
{
    struct ITEM a[50];
    int n, i, j;
    float cap, rem, profit;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &a[i].item_profit, &a[i].item_weight);
        a[i].item_id = i + 1;
        a[i].profit_weight_ratio = a[i].item_profit / a[i].item_weight;
        a[i].amount = 0;
    }
    printf("Enter the capacity of knapsack:");
    scanf("%f", &cap);

    heapsort(a, n);
    for (i = 0, j = n - 1; i < j; i++, j--)
        swap(&a[i], &a[j]);

    rem = cap;
    profit = 0;
    for (i = 0; i < n; i++)
    {
        if (a[i].item_weight <= rem)
        {
            a[i].amount = 1;
            rem -= a[i].item_weight;
            profit += a[i].item_profit;
        }
        else if (rem > 0)
        {
            a[i].amount = rem / a[i].item_weight;
            profit += a[i].item_profit * a[i].amount;
            rem = 0;
        }
        else
            a[i].amount = 0;
    }

    printf("Item No\tprofit\tWeight\tAmount to be taken\n");
    for (i = 0; i < n; i++)
        printf("%d\t%f\t%f\t%f\n", a[i].item_id, a[i].item_profit, a[i].item_weight, a[i].amount);
    printf("Maximum profit: %f\n", profit);
    return 0;
}
