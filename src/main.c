#include <stdio.h>
#include <stdlib.h>

#include "lib/map.h"
#include "lib/prim.h"
#include "lib/compression.h"

int main()
{
    printf("\nPartie 1 : Graphe et application\n\n");
    int **map = map_read("res/carte.txt");
    struct city *cities = get_cities(map);
    struct link **link_matrix = compute_link_matrix("res/links", map, cities);
    int **int_link_matrix = link_matrix_to_int(link_matrix);
    int *solution = prim_algo(int_link_matrix);
    save_solution(solution, cities);

    printf("\nPartie 2 : Compression\n\n");

    compress_map("res/carte.txt");
    decompress_map();

    printf("\nCompressed map :\n\n");
    print_compressed_map();

    printf("\nDecompressed map :\n\n");
    print_decompressed_map();

    compression_effectiveness("res/carte.txt");

    rle_compress_solution("res/solution.txt", "res/solution_compressed.txt");
    rle_decompress_solution("res/solution_compressed.txt", "res/solution_decompressed.txt");

    return 0;
}
