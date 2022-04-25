#include <stdio.h>
#include <stdlib.h>
#include "lib/map.h"

int main()
{

    int **map = map_read("res/carte.txt");
    struct city *cities = get_cities(map);

    struct link **link_matrix = compute_link_matrix("res/links", map, cities);
    link_matrix_print(link_matrix);

    return 0;
}
