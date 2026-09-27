#include <stdio.h>

#define INF 99999

int main()
{
    int n, s, i, j, u, v, min, total;
    int g[20][20], t[20][20], key[20], parent[20], vis[20];
    FILE *fp;

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &s);

    fp = fopen("inUnAdjMat.dat", "r");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            fscanf(fp, "%d", &g[i][j]);
    fclose(fp);

    for (i = 1; i <= n; i++)
    {
        key[i] = INF;
        vis[i] = 0;
        parent[i] = -1;
        for (j = 1; j <= n; j++)
            t[i][j] = 0;
    }
    key[s] = 0;

    for (i = 1; i <= n; i++)
    {
        min = INF;
        u = -1;
        for (v = 1; v <= n; v++)
        {
            if (!vis[v] && key[v] <= min)
            {
                min = key[v];
                u = v;
            }
        }
        if (u == -1)
            break;
        vis[u] = 1;
        for (v = 1; v <= n; v++)
        {
            if (!vis[v] && g[u][v] != 0 && g[u][v] < key[v])
            {
                key[v] = g[u][v];
                parent[v] = u;
            }
        }
    }

    total = 0;
    for (v = 1; v <= n; v++)
    {
        if (parent[v] != -1)
        {
            t[parent[v]][v] = g[parent[v]][v];
            t[v][parent[v]] = g[v][parent[v]];
            total += g[parent[v]][v];
        }
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            printf("%d\t", t[i][j]);
        printf("\n");
    }
    printf("Total Weight of the Spanning Tree: %d\n", total);
    return 0;
}
