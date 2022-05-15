#ifndef PRIM
#define PRIM

#define INF 9999999
#define V 17

int *prim_algo(int **G);
void save_solution(int *solution, struct city *cities);
void prim_test(int **cost);

#endif
