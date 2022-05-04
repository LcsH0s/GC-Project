#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"
#include "prim.h"

int *prim_algo(int **G)
{
    int no_edge;
    int selected[V];
    int final_solution[V];
    memset(selected, false, sizeof(selected));
    no_edge = 0;
    selected[0] = true;
    int count = 0;

    int x;
    int y;
    printf("Edge : Weight\n");

    while (no_edge < V - 1)
    {
        int min = INF;
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
        printf("%d - %d : %d\n", x, y, G[x][y]);
        final_solution[count] = x + 1;
        selected[y] = true;
        no_edge++;
        count++;
    }
    final_solution[count] = y + 1;
    return final_solution;
}

void save_solution(int *solution, struct city *cities)
{
    for (int i = 0; i < 17; i++)
    {
        FILE *f = fopen("solution.txt", "w");
        fprintf("%s -> ", cities[solution[i]].name);
    }
}