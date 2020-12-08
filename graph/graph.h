#ifndef GRAPH_H
#define GRAPH_H

#define INF (~((unsigned int)0))
typedef struct Vertex {
    char name[32];
    int index;
    struct Vertex *next;
    int weight;
} Vertex;

typedef struct Graph {
    int num_vertex;
    Vertex *adjacency_list[0];
} Graph;

typedef void (*callback)(Vertex*,Graph*);

extern Graph *build_graph();
extern void print_graph(Graph *G);
extern void TopSort(Graph *G, callback cb);
extern void free_graph(Graph *G);
extern void unweighted_breadth_first(Graph *G, int start_with, callback cb);
#endif
