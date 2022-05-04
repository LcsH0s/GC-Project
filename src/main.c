#include <stdio.h>
#include <stdlib.h>

#include "lib/map.h"
#include "lib/prim.h"

int main()
{

    int **map = map_read("res/carte.txt");
    struct city *cities = get_cities(map);
    struct link **link_matrix = compute_link_matrix("res/links", map, cities);
    int **int_link_matrix = link_matrix_to_int(link_matrix);

    map_print(map);

    link_matrix_print(link_matrix);
    int *solution = prim_algo(int_link_matrix);
    save_solution(solution, cities);
    // Pour la compression : algo RLE

    return 0;
}
