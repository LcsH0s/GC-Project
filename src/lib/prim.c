#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"
#include "prim.h"

int *prim_algo(int **G)
{
    int no_edge;
    int selected[V];
    int *final_solution = malloc(sizeof(int) * V);
    memset(selected, 0, sizeof(selected));
    no_edge = 0;
    selected[0] = 1;
    int count = 0;
    int total = 0;
    int min;
    int x;
    int y;

    while (no_edge < V - 1)
    {
        min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < V; j++)
                {
                    if (!selected[j] && G[i][j])
                    {
                        if (min > G[i][j])
                        {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        printf("%d - %d : %d\n", x + 1, y + 1, G[x][y]);
        total += G[x][y];
        final_solution[count] = x + 1;
        selected[y] = 1;
        no_edge++;
        count++;
    }
    printf("Total: %d\n", total);
    final_solution[count] = y + 1;
    return final_solution;
}

void prim_test(int **cost)
{
    int a, b, u, v, n = 16, i, j, ne = 1;
    int visited[17] = {0}, min, mincost = 0;

    for (int k = 0; k <= n; k++)
    {
        for (int l = 0; l <= n; l++)
        {
            if (cost[k][l] == 0)
            {
                cost[k][l] = 999;
            }
        }
    }

    visited[1] = 1;
    printf("\n");
    while (ne < n)
    {
        for (i = 1, min = 999; i <= n; i++)

            for (j = 1; j <= n; j++)

                if (cost[i][j] < min)

                    if (visited[i] != 0)
                    {
                        min = cost[i][j];
                        a = u = i;
                        b = v = j;
                    }

        if (visited[u] == 0 || visited[v] == 0)
        {
            printf("\n Edge %d:(%d %d) cost:%d", ne++, a, b, min);
            mincost += min;
            visited[b] = 1;
        }
        cost[a][b] = cost[b][a] = 999;
    }
    printf("\n Minimun cost=%d", mincost);
}

void save_solution(int *solution, struct city *cities)
{
    FILE *f = fopen("res/solution.txt", "w");
    for (int i = 0; i < 16; i++)
    {
        if (cities[solution[i + 1]].name != NULL)
            fprintf(f, "%s ----> ", cities[solution[i]].name);
        else
            fprintf(f, "%s", cities[solution[i]].name);
    }
    fclose(f);
}
