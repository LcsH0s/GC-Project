#include <stdio.h>
#include <stdlib.h>

int main()
{

    int c;
    FILE *carte;
    carte = fopen("carte.txt", "r");
    if (carte == NULL)
    {
        printf("Cannot open file");
        exit(-1);
    }
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; i < 26; j++)
            fscanf(carte, " %d", &c);
    }

    return 0;
}