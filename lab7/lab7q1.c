#include <stdio.h>

#define INF 99999

void printpath(int pred[], int v)
{
    if (pred[v] == -1)
        return;
    printpath(pred, pred[v]);
    printf("%d->", pred[v]);
}

int main()
{
    int n, s, i, j, u, v, min, count;
    int g[20][20], dist[20], vis[20], pred[20];
    FILE *fp;

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Source Vertex: ");
    scanf("%d", &s);

    fp = fopen("inDiAdjMat1.dat", "r");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            fscanf(fp, "%d", &g[i][j]);
    fclose(fp);

    for (i = 1; i <= n; i++)
    {
        dist[i] = INF;
        vis[i] = 0;
        pred[i] = -1;
    }
    dist[s] = 0;

    for (count = 1; count <= n; count++)
    {
        min = INF;
        u = -1;
        for (v = 1; v <= n; v++)
        {
            if (!vis[v] && dist[v] < min)
            {
                min = dist[v];
                u = v;
            }
        }
        if (u == -1)
            break;
        vis[u] = 1;
        for (v = 1; v <= n; v++)
        {
            if (!vis[v] && g[u][v] != 0 && dist[u] + g[u][v] < dist[v])
            {
                dist[v] = dist[u] + g[u][v];
                pred[v] = u;
            }
        }
    }

    printf("Source\tDestination\tCost\tPath\n");
    for (i = 1; i <= n; i++)
    {
        printf("%d\t%d\t%d\t", s, i, dist[i]);
        if (i == s)
            printf("-\n");
        else
        {
            printpath(pred, i);
            printf("%d\n", i);
        }
    }
    return 0;
}
