#ifndef MAP
#define MAP

struct coordinates
{
    int x;
    int y;
};

struct city
{
    int code;
    struct coordinates cords;
};

struct link
{
    float distance;
};

int **map_read(char *name);
void map_print(int **map);
struct city *get_cities(int **map);
int **links_read(const char *filename);
struct link **compute_link_matrix(const char *filename, int **map, struct city *cities);
void link_matrix_print(struct link **link_matrix);

#endif
