#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"

struct record {
    int known;
    unsigned int distance;
    Vertex *prev;
};

static Graph *add_vertex(int index, Graph *G, Vertex *prev, int weight, unsigned int *raw, int size)
{
    Vertex *V;
    Vertex *p;
    int i;

    V = malloc(sizeof(Vertex));
    if (V == NULL)
    {
        printf("Malloc vertex error\n");
        exit(1);
    }

    snprintf(V->name, 32, "V%d", index+1);
    V->index = index;
    V->next = NULL;
    if (prev == NULL) // list head
    {
        G->adjacency_list[index] = V;
        for (i = 0; i < size; i++)
        {
            if (raw[i] != INF && raw[i] != 0)
            {
                add_vertex(i, G, V, raw[i], NULL, size);
            }
        }
    }
    else
    {
        p = prev;
        while (p->next != NULL) p = p->next;
        p->next = V;
        V->weight = weight;
    }
    return G;
}

Graph *build_graph(unsigned int *table, int size)
{
    int index = size;
    
    Graph *G = malloc(sizeof(Graph) + size * sizeof(Vertex *));

    if (G == NULL)
    {
        printf("Malloc failed\n");
        exit(1);
    }

    G->num_vertex = size;
    while(index--)
        add_vertex(index, G, NULL, 0, &table[index * size], size);

    return G;
}

void free_graph(Graph *G)
{
    Vertex *V,*next;
    int i;
    if (G != NULL)
    {
        for(i = 0; i < G->num_vertex; i++)
        {
            V = G->adjacency_list[i];
            next = V->next;
            free(V);
            while(next != NULL)
            {
                V = next;
                next = next->next;
                free(V);
            }
        }
        free(G);
    }
}

void print_graph(Graph *G)
{
    int i;
    Vertex *V;
    for(i = 0; i < G->num_vertex; i++)
    {
        V = G->adjacency_list[i];
        printf("[%s]", V->name);
        while((V = V->next) != NULL)
        {
            printf("---%d--->[%s]", V->weight, V->name);
        }
        printf("\n");
    }
}

static void CalculateIndegree(Graph *G, int *indegree)
{
    int i;
    memset(indegree, 0, sizeof(int)*(G->num_vertex));
    for (i = 0; i < G->num_vertex; i++)
    {
        Vertex *p = G->adjacency_list[i]->next;
        while(p != NULL)
        {
            indegree[p->index]++;
            p = p->next;
        }
    }
}

static Vertex *FindNewVertexOfIndegreeZero(Graph *G, int *indegree)
{
    int i;
    for (i = 0; i < G->num_vertex; i++)
    {
        if (indegree[i] == 0)
        {
            indegree[i]--;
            return G->adjacency_list[i];
        }
    }
    return NULL;
}

void TopSort(Graph *G, callback cb)
{
    int counter;
    Vertex *V, *W;

    int indegree[G->num_vertex];
    
    CalculateIndegree(G, indegree);

    for (counter = 0; counter < G->num_vertex; counter++)
    {
        V = FindNewVertexOfIndegreeZero(G, indegree);
        if (V == NULL)
        {
            printf("Graph has a cycle\n");
            break;
        }
        if (cb != NULL) (*cb)(V, G);
        W = V->next;
        while(W != NULL)
        {
            indegree[W->index]--;
            W = W->next;
        }
    }
}

void unweighted_breadth_first(Graph *G, int start_with, callback cb)
{
    struct record table[G->num_vertex];
    int queue[G->num_vertex];
    int i;
    int s = 0;
    int e = 0;
    Vertex *p;
    for (i = 0; i < G->num_vertex; i++)
    {
        table[i].known = (i == start_with)?1:0;
        table[i].distance = (i == start_with)?0:INF;
        table[i].prev = NULL;
    }

    printf("enqueue %d\n", start_with + 1);
    queue[e++] = start_with;

    while (s < e) {
        p = G->adjacency_list[queue[s]];
        printf("dequeue %d\n", p->index + 1);
        
        while ((p = p->next) != NULL)
        {
            if (table[p->index].known == 0)
            {
                table[p->index].distance = table[queue[s]].distance + 1;
                table[p->index].prev = G->adjacency_list[queue[s]];
                table[p->index].known = 1;
                printf("enqueue %d\n", p->index + 1);
                queue[e++] = p->index;
            }
        }
        s++;
    }

    for (i = 0; i < G->num_vertex; i++)
    {
        printf("known=%d, distance=%d, prev is ", table[i].known, table[i].distance);
        cb(table[i].prev, G);
    }
}

void weighted_breadth_first(Graph *G, int start_with, callback cb)
{
    struct record table[G->num_vertex];
    int queue[G->num_vertex];
    int i;
    int s = 0;
    int e = 0;
    Vertex *p;
    for (i = 0; i < G->num_vertex; i++)
    {
        table[i].known = (i == start_with)?1:0;
        table[i].distance = (i == start_with)?0:INF;
        table[i].prev = NULL;
    }

    printf("enqueue %d\n", start_with + 1);
    queue[e++] = start_with;

    while (s < e) {
        p = G->adjacency_list[queue[s]];
        printf("dequeue %d\n", p->index + 1);
        
        while ((p = p->next) != NULL)
        {
            if (table[p->index].distance > table[queue[s]].distance + p->weight)
            {
                table[p->index].distance = table[queue[s]].distance + p->weight;
                table[p->index].prev = G->adjacency_list[queue[s]];
                table[p->index].known = 1;
                printf("enqueue %d\n", p->index + 1);
                queue[e++] = p->index;
            }
        }
        s++;
    }

    for (i = 0; i < G->num_vertex; i++)
    {
        printf("known=%d, distance=%d, prev is ", table[i].known, table[i].distance);
        cb(table[i].prev, G);
    }
}








