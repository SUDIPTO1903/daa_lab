#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

struct person *p;
int n;

void printname(char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '_')
            printf(" ");
        else
            printf("%c", s[i]);
    }
}

void swap(struct person *a, struct person *b)
{
    struct person t;
    t = *a;
    *a = *b;
    *b = t;
}

void minheapify(int i, int sz)
{
    int smallest, l, r;
    smallest = i;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < sz && p[l].age < p[smallest].age)
        smallest = l;
    if (r < sz && p[r].age < p[smallest].age)
        smallest = r;
    if (smallest != i)
    {
        swap(&p[i], &p[smallest]);
        minheapify(smallest, sz);
    }
}

void maxheapify(int i, int sz)
{
    int largest, l, r;
    largest = i;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < sz && p[l].weight > p[largest].weight)
        largest = l;
    if (r < sz && p[r].weight > p[largest].weight)
        largest = r;
    if (largest != i)
    {
        swap(&p[i], &p[largest]);
        maxheapify(largest, sz);
    }
}

void buildmin()
{
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        minheapify(i, n);
}

void buildmax()
{
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        maxheapify(i, n);
}

void display()
{
    int i;
    printf("Id\tName\t\t\tAge\tHeight\tWeight(pound)\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t", p[i].id);
        printname(p[i].name);
        printf("\t\t%d\t%d\t%d\n", p[i].age, p[i].height, p[i].weight);
    }
}

void readdata()
{
    FILE *fp;
    char temp[50];
    int i, id, age, h, w;
    fp = fopen("students.dat", "r");
    n = 0;
    while (fscanf(fp, "%d %s %d %d %d", &id, temp, &age, &h, &w) == 5)
        n++;
    rewind(fp);
    p = (struct person *)malloc(n * sizeof(struct person));
    i = 0;
    while (fscanf(fp, "%d %s %d %d %d", &id, temp, &age, &h, &w) == 5)
    {
        p[i].id = id;
        p[i].name = (char *)malloc(strlen(temp) + 1);
        strcpy(p[i].name, temp);
        p[i].age = age;
        p[i].height = h;
        p[i].weight = w;
        i++;
    }
    fclose(fp);
    display();
}

void youngest()
{
    int i, min, wi;
    if (n == 0)
        return;
    min = p[0].age;
    wi = p[0].weight;
    for (i = 1; i < n; i++)
    {
        if (p[i].age < min)
        {
            min = p[i].age;
            wi = p[i].weight;
        }
    }
    printf("Weight of youngest student: %.2f kg\n", wi * 0.453592);
}

void insertmin()
{
    int id, age, h, w;
    char temp[50];
    int i;
    printf("Enter id name age height weight: ");
    scanf("%d %s %d %d %d", &id, temp, &age, &h, &w);
    n++;
    p = (struct person *)realloc(p, n * sizeof(struct person));
    i = n - 1;
    p[i].id = id;
    p[i].name = (char *)malloc(strlen(temp) + 1);
    strcpy(p[i].name, temp);
    p[i].age = age;
    p[i].height = h;
    p[i].weight = w;
    while (i > 0 && p[(i - 1) / 2].age > p[i].age)
    {
        swap(&p[i], &p[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    display();
}

void deleteoldest()
{
    int i, maxi;
    if (n == 0)
        return;
    maxi = 0;
    for (i = 1; i < n; i++)
    {
        if (p[i].age > p[maxi].age)
            maxi = i;
    }
    free(p[maxi].name);
    p[maxi] = p[n - 1];
    n--;
    p = (struct person *)realloc(p, n * sizeof(struct person));
    buildmin();
    display();
}

int main()
{
    int ch;
    p = NULL;
    n = 0;
    while (1)
    {
        printf("MAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &ch);
        if (ch == 1)
            readdata();
        else if (ch == 2)
        {
            buildmin();
            display();
        }
        else if (ch == 3)
        {
            buildmax();
            display();
        }
        else if (ch == 4)
            youngest();
        else if (ch == 5)
            insertmin();
        else if (ch == 6)
            deleteoldest();
        else if (ch == 7)
            break;
    }
    return 0;
}
