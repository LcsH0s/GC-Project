#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "map.h"

int **map_read(char *filename)
{
    FILE *fmap = fopen(filename, "r");

    if (fmap == NULL)
    {
        printf("File Name Error: \"%s\" No such file ", filename);
        exit(-1);
    }

    int c;
    int **map = malloc(sizeof(int *) * 22);

    for (int i = 0; i < 22; i++)
    {
        map[i] = malloc(sizeof(int) * 26);
    }

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            fscanf(fmap, " %d", &c);
            map[i][j] = c;
        }
    }
    return map;
}

void map_print(int **map)
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

char *get_city_name_by_code(int code)
{
    switch (code)
    {
    case 1:
        return "Lille";
    case 2:
        return "Paris";
    case 3:
        return "Brest";
    case 4:
        return "Rennes";
    case 5:
        return "Strasbourg";
    case 6:
        return "Orlean";
    case 7:
        return "Nantes";
    case 8:
        return "Dijon";
    case 9:
        return "Clermont-Ferrand";
    case 10:
        return "Lyon";
    case 11:
        return "Geneve";
    case 12:
        return "Bordeaux";
    case 13:
        return "Genoble";
    case 14:
        return "Nice";
    case 15:
        return "Toulouse";
    case 16:
        return "Montpellier";
    case 17:
        return "Perpignan";
    default:
        return "lol";
    }
}

struct city *get_cities(int **map)
{
    struct city *cities = malloc(sizeof(struct city) * 17);
    int c = 0;

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (map[i][j] != 0)
            {
                cities[c].code = map[i][j];
                cities[c].name = malloc(sizeof(char) * 30);
                strcpy(cities[c].name, get_city_name_by_code(cities[c].code));
                cities[c].cords.x = i;
                cities[c].cords.y = j;
                c++;
            }
        }
    }
    return cities;
}

int **links_read(const char *filename)
{
    FILE *flinks = fopen(filename, "r");

    if (flinks == NULL)
    {
        printf("File Name Error: \"%s\" No such file ", filename);
        exit(-1);
    }

    int origin, destination;
    int **links = malloc(sizeof(int *) * 17);

    for (int i = 0; i < 17; i++)
    {
        links[i] = malloc(sizeof(int) * 10);
        for (int j = 0; j < 10; j++)
        {
            links[i][j] = 0;
        }
    }

    fscanf(flinks, "%d", &origin);
    fscanf(flinks, "%d", &destination);

    for (int i = 0; origin != -1; i++)
    {
        for (int j = 0; destination != 0; j++)
        {
            links[i][j] = destination;
            fscanf(flinks, " %d", &destination);
        }
        fscanf(flinks, "%d", &origin);
        fscanf(flinks, " %d", &destination);
    }
    return links;
}

double compute_distance(struct city *cities, int city_code_a, int city_code_b)
{
    return (sqrt(pow(cities[city_code_a].cords.x - cities[city_code_b].cords.x, 2) + pow(cities[city_code_a].cords.y - cities[city_code_b].cords.y, 2))) * 10;
}

int is_linked(int **links, int city_code_a, int city_code_b)
{
    for (int i = 0; i < 10; i++)
    {
        if (links[city_code_a - 1][i] == city_code_b)
            return 1;
    }
    return 0;
}

struct link **compute_link_matrix(const char *filename, int **map, struct city *cities)
{

    struct link **link_matrix = malloc(sizeof(struct link *) * 17);
    int **links = links_read(filename);

    for (int i = 0; i < 17; i++)
    {
        link_matrix[i] = malloc(sizeof(struct link) * 17);
        for (int j = 0; j < 17; j++)
        {
            if (is_linked(links, i + 1, j + 1))
                link_matrix[i][j].distance = compute_distance(cities, i + 1, j + 1);
            else
                link_matrix[i][j].distance = 0;
        }
    }
    return link_matrix;
}

void link_matrix_print(struct link **link_matrix)
{
    printf("  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17\n");
    for (int i = 0; i < 17; i++)
    {
        if (i + 1 > 10)
            printf("%d ", i + 1);
        else
            printf("%d  ", i + 1);

        for (int j = 0; j < 17; j++)
        {
            if (link_matrix[i][j].distance != 0)
            {
                if (link_matrix[i][j].distance > 10)
                    printf("%.0f ", link_matrix[i][j].distance);
                else
                    printf("%.0f  ", link_matrix[i][j].distance);
            }
            else
                printf("   ");
        }
        printf("\n");
    }
}

int **link_matrix_to_int(struct link **link_matrix)
{
    int **matrix = malloc(sizeof(int *) * 17);
    for (int i = 0; i < 17; i++)
    {
        matrix[i] = malloc(sizeof(int) * 17);
        for (int j = 0; j < 17; j++)
        {
            matrix[i][j] = round(link_matrix[i][j].distance);
        }
    }
    return matrix;
}
