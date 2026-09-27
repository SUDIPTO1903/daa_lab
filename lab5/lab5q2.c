#include <stdio.h>
#include <stdlib.h>

struct SYMBOL
{
    char alphabet;
    int frequency;
};

struct node
{
    char ch;
    int freq;
    struct node *l, *r;
};

struct node *h[100];
int hs;

void swapn(int i, int j)
{
    struct node *t;
    t = h[i];
    h[i] = h[j];
    h[j] = t;
}

void heapifyup(int i)
{
    while (i > 0 && h[(i - 1) / 2]->freq > h[i]->freq)
    {
        swapn(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void heapifydown(int i)
{
    int smallest, l, r;
    smallest = i;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < hs && h[l]->freq < h[smallest]->freq)
        smallest = l;
    if (r < hs && h[r]->freq < h[smallest]->freq)
        smallest = r;
    if (smallest != i)
    {
        swapn(i, smallest);
        heapifydown(smallest);
    }
}

void insertq(struct node *x)
{
    h[hs] = x;
    hs++;
    heapifyup(hs - 1);
}

struct node *extractmin()
{
    struct node *m;
    m = h[0];
    hs--;
    h[0] = h[hs];
    heapifydown(0);
    return m;
}

void inorder(struct node *t)
{
    if (t == NULL)
        return;
    inorder(t->l);
    if (t->ch != '\0')
        printf("%c  ", t->ch);
    inorder(t->r);
}

int main()
{
    struct SYMBOL s[50];
    struct node *x, *y, *z;
    int n, i;
    hs = 0;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);
    printf("Enter the alphabets: ");
    for (i = 0; i < n; i++)
        scanf(" %c", &s[i].alphabet);
    printf("Enter its frequencies: ");
    for (i = 0; i < n; i++)
        scanf("%d", &s[i].frequency);
    for (i = 0; i < n; i++)
    {
        x = (struct node *)malloc(sizeof(struct node));
        x->ch = s[i].alphabet;
        x->freq = s[i].frequency;
        x->l = NULL;
        x->r = NULL;
        insertq(x);
    }
    while (hs > 1)
    {
        x = extractmin();
        y = extractmin();
        z = (struct node *)malloc(sizeof(struct node));
        z->ch = '\0';
        z->freq = x->freq + y->freq;
        z->l = x;
        z->r = y;
        insertq(z);
    }
    printf("In-order traversal of the tree (Huffman): ");
    inorder(h[0]);
    printf("\n");
    return 0;
}
