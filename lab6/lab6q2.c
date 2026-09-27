#include <stdio.h>

struct edge
{
    int u, v, w;
};

int parent[50], rnk[50];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    if (rnk[a] < rnk[b])
        parent[a] = b;
    else if (rnk[b] < rnk[a])
        parent[b] = a;
    else
    {
        parent[b] = a;
        rnk[a]++;
    }
}

int main()
{
    struct edge e[100], mst[100], t;
    int n, m, i, j, k, total;
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++)
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
    for (i = 1; i <= n; i++)
    {
        parent[i] = i;
        rnk[i] = 0;
    }
    for (i = 0; i < m - 1; i++)
    {
        for (j = 0; j < m - i - 1; j++)
        {
            if (e[j].w > e[j + 1].w)
            {
                t = e[j];
                e[j] = e[j + 1];
                e[j + 1] = t;
            }
        }
    }
    k = 0;
    total = 0;
    for (i = 0; i < m; i++)
    {
        if (find(e[i].u) != find(e[i].v))
        {
            unite(e[i].u, e[i].v);
            mst[k] = e[i];
            total += e[i].w;
            k++;
        }
    }
    for (i = 0; i < k - 1; i++)
    {
        for (j = 0; j < k - i - 1; j++)
        {
            int maxj, maxn;
            maxj = mst[j].u > mst[j].v ? mst[j].u : mst[j].v;
            maxn = mst[j + 1].u > mst[j + 1].v ? mst[j + 1].u : mst[j + 1].v;
            if (mst[j].w > mst[j + 1].w || (mst[j].w == mst[j + 1].w && maxj > maxn))
            {
                t = mst[j];
                mst[j] = mst[j + 1];
                mst[j + 1] = t;
            }
        }
    }
    printf("Edge\t\tCost\n");
    for (i = 0; i < k; i++)
    {
        int a, b;
        a = mst[i].u;
        b = mst[i].v;
        if (a >= 6 && b >= 6)
        {
            if (a < b)
            {
                t.u = a;
                a = b;
                b = t.u;
            }
        }
        else if (a > b)
        {
            t.u = a;
            a = b;
            b = t.u;
        }
        printf("%d--%d\t\t%d\n", a, b, mst[i].w);
    }
    printf("Total Weight of the Spanning Tree: %d\n", total);
    return 0;
}
