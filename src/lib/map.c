#include <stdlib.h>
#include <stdio.h>

#include "map.h"

int **map_read(char *name)
{
    FILE *fmap = fopen(name, "r");

    if (fmap == NULL)
    {
        printf("File Name Error: \"%s\" No such file ", name);
        exit(-1);
    }

    int c;
    int map[22][26];

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            fscanf(map, " %d", c);
            map[i][j] = c;
        }
    }
}

void print_map(int **map)
{

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}