#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct graph
{
    int num_nodes;
    bool **edges;
};

graph*
create_graph(int num_nodes)
{
    graph *g = malloc(sizeof(*g));
    if (g == NULL)
    {
        return NULL;
    }

    g->num_nodes = num_nodes;

    g->edges = calloc(sizeof(bool *), g->num_nodes);
    if (g->edges == NULL)
    {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->num_nodes; i++)
    {
        g->edges[i] = calloc(sizeof(bool), g->num_nodes);
        if (g->edges == NULL)
        {
            destroy_graph(g);
            return NULL;
        }
    }
    return g;
}

void
destroy_graph(graph *graph)
{
    if (graph->edges == NULL)
        return;

    for (int i = 0; i < graph->num_nodes; i++)
    {
        if (graph->edges[i] != NULL)
        {
            free(graph->edges[i]);
        }
    }
    free(graph->edges);
    free(graph);
}

void
print_graph(graph *graph)
{
    printf("digraph {\n");
    for (int from = 0; from < graph->num_nodes; from++)
    {
        for (int to = 0; to < graph->num_nodes; to++)
        {
            if (graph->edges[from][to])
            {
                printf("%d -> %d;\n", from, to);
            }
        }
    }
    printf("}\n");
}

bool
add_edge(graph *graph, unsigned int from, unsigned int to)
{
    if (has_edge(graph, from, to))
        return false;

    graph->edges[from][to] = true;
    return true;
}

bool
has_edge(graph *graph, unsigned int from, unsigned int to)
{
    return graph->edges[from][to];
}
