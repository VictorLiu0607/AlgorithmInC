#include <stdio.h>
#include "graph.h"

unsigned int graphA[7][7] = {
    {0  ,2  ,4  ,1  ,INF,INF,INF},
    {2  ,0  ,INF,3  ,10 ,INF,INF},
    {4  ,INF,0  ,2  ,INF,5  ,INF},
    {1  ,3  ,2  ,0  ,7  ,8  ,4},
    {INF,10 ,INF,7  ,0  ,INF,6},
    {INF,INF,5  ,8  ,INF,0  ,1},
    {INF,INF,INF,4  ,6  ,1  ,0}
};
int VERTEX_SIZE=7;

unsigned int graphTopSort[7][7] = {
    {0,1,0,1,0,0,0},
    {0,0,0,1,1,0,0},
    {1,0,0,0,0,1,0},
    {0,0,1,0,0,1,1},
    {0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0}
};

void print_vertex(Vertex* V, Graph *G)
{
    if (V) printf("%s\n",V->name);
}

int main(int argc, char *argv[])
{
    Graph *G = build_graph(graphTopSort, VERTEX_SIZE);

    print_graph(G);

    TopSort(G, print_vertex);

    unweighted_breadth_first(G, 2, print_vertex);

    free_graph(G);

    return 0;
}
