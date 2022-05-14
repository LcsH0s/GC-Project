#include <stdio.h>
#include <stdlib.h>

#include "compression.h"

void compress_map(char *filename)
{
    FILE *fmap = fopen(filename, "r");
    FILE *comp_map = fopen("res/compressed_map.txt", "w");
    int zero_count = 0;
    int c;

    if (fmap == NULL)
    {
        printf("File Name Error: \"%s\" No such file ", filename);
        exit(-1);
    }
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            fscanf(fmap, " %d", &c);
            if (c == 0)
            {
                zero_count++;
            }
            else
            {
                fprintf(comp_map, "$%d %d", zero_count, c);
                zero_count = 0;
            }
        }
        if (zero_count != 0)
        {
            fprintf(comp_map, "$%d ", zero_count);
            zero_count = 0;
        }
        fprintf(comp_map, "\n");
    }
    fclose(fmap);
    fclose(comp_map);
}

void compression_effectiveness(char *filename)
{
    char c = 0;
    double count_nc = 0, count_c = 0;

    FILE *fmap = fopen(filename, "r");
    FILE *comp_map = fopen("res/compressed_map.txt", "r");

    for (c = getc(fmap); c != EOF; c = getc(fmap))
    {
        count_nc = count_nc + 1;
    }

    c = 0;

    for (c = getc(comp_map); c != EOF; c = getc(comp_map))
    {
        count_c = count_c + 1;
    }

    printf("\nCompression rate : %.1f%% \n", ((count_nc - count_c) / count_nc) * 100);

    fclose(fmap);
    fclose(comp_map);
}

void decompress_map()
{
    FILE *comp_map = fopen("res/compressed_map.txt", "r");
    FILE *decomp_map = fopen("res/decompressed_map.txt", "w");

    int num;
    int num_zero = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (comp_map == NULL)
    {
        printf("File Name Error: \"res/compressed_map.txt\" No such file ");
        exit(-1);
    }

    while ((read = getline(&line, &len, comp_map)) != -1)
    {
        for (int i = 0; i < read - 2; i++)
        {
            if (line[i] == ' ')
            {
                continue;
            }

            else if (line[i] == '$')
            {
                if ((line[i + 2] <= '9') & (line[i + 2] >= '0'))
                {
                    num_zero = (line[i + 1] - '0') * 10 + (line[i + 2] - '0');
                    i += 2;
                    for (int j = 0; j < num_zero; j++)
                        fprintf(decomp_map, "0 ");
                    continue;
                }
                else
                {
                    num_zero = (line[i + 1] - '0');
                    i++;
                    for (int j = 0; j < num_zero; j++)
                        fprintf(decomp_map, "0 ");
                    continue;
                }
            }
            else
            {
                if ((line[i + 1] <= '9') & (line[i + 1] >= '0'))
                {
                    num = ((line[i] - '0') * 10 + (line[i + 1] - '0'));
                    i += 1;
                    fprintf(decomp_map, "%d ", num);
                    continue;
                }
                else if ((line[i] <= '9') & (line[i] >= '0'))
                {
                    fprintf(decomp_map, "%c ", line[i]);
                    continue;
                }
            }
        }
        fprintf(decomp_map, "\n");
    }
    fclose(decomp_map);
    fclose(comp_map);
}

void print_compressed_map()
{
    FILE *comp_map = fopen("res/compressed_map.txt", "r");
    char str[99999];
    fscanf(comp_map, "%[^\0]", str);
    printf("%s", str);
}

void print_decompressed_map()
{
    FILE *decomp_map = fopen("res/decompressed_map.txt", "r");
    char str[99999];
    fscanf(decomp_map, "%[^\0]", str);
    printf("%s", str);
}

void rle_compress(const char *src, const char *dst)
{
    FILE *in, *out;
    uint8_t t[129];
    int i, keep;

    // file verification
    if (!(in = fopen(src, "rb")))
        exit(-1);
    if (!(out = fopen(dst, "wb")))
    {
        fclose(in);
        exit(-1);
    }
    t[0] = fgetc(in);
    while (!feof(in))
    {
        t[1] = fgetc(in);
        if (t[0] != t[1])
        {
            i = 1;
            if (!feof(in))
                do
                    t[++i] = fgetc(in);
                while (!feof(in) && i < 128 && t[i] != t[i - 1]);
            if ((keep = t[i] == t[i - 1]))
                --i;
            if (fputc(i - 1, out) == EOF ||
                fwrite(t, sizeof(uint8_t), i, out) < (unsigned)i)
                break;
            t[0] = t[i];
            if (!keep)
                continue;
        }
        i = 2;
        do
            t[1] = fgetc(in);
        while (++i < 130 && t[0] == t[1]);
        if (fputc(i + 125, out) == EOF ||
            fputc(t[0], out) == EOF)
            break;
        t[0] = t[1];
    }
    fclose(in);
    fclose(out);
}

void rle_extract(const char *src, const char *dst)
{
    FILE *in, *out;
    int i, j, max;

    if (!(in = fopen(src, "rb")))
        exit(-1);
    if (!(out = fopen(dst, "wb")))
    {
        fclose(in);
        exit(-1);
    }
    j = 0;
    while ((i = fgetc(in)) != EOF && (j = fgetc(in)) != EOF)
    {
        max = i + (i < 128 ? 1 : -126);
        while (max--)
            if (fputc(j, out) == EOF ||
                (i < 128 && max && (j = fgetc(in)) == EOF))
                break;
    }

    fclose(in);
    fclose(out);
}