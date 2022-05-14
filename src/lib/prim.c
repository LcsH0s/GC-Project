#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map.h"
#include "prim.h"

int *prim_algo(int **G)
{
    int no_edge;
    int selected[V];
    int *final_solution = malloc(sizeof(int) * V);
    memset(selected, false, sizeof(selected));
    no_edge = 0;
    selected[0] = true;
    int count = 0;
    int total = 0;
    int x;
    int y;

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
        printf("%d - %d : %d\n", x + 1, y + 1, G[x][y]);
        total += G[x][y];
        final_solution[count] = x + 1;
        selected[y] = true;
        no_edge++;
        count++;
    }
    printf("Total: %d\n", total);
    final_solution[count] = y + 1;
    return final_solution;
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
