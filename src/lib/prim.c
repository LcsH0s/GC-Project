#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"
#include "prim.h"

void prim_algo(int **cost)
{
    int a, b, u, v, n = 16, i, j, ne = 1;
    int visited[17] = {0}, min, mincost = 0;
    FILE *fsolution = fopen("res/solution.txt", "w");

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
            printf("\n%d:(%d %d)", ne++, a, b);
            fprintf(fsolution, "%d -------> %d\n", a, b);
            mincost += min;
            visited[b] = 1;
        }
        cost[a][b] = cost[b][a] = 999;
    }
    printf("\nCout minimal=%d\n", mincost);
    fclose(fsolution);
}
