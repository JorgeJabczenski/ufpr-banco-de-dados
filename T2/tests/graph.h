#ifndef GRAPH
#define GRAPH

#include <stdbool.h>

typedef struct graph graph;

graph * create_graph(int num_nodes);
void destroy_graph(graph *graph);
void print_graph(graph *graph);
bool add_edge(graph *graph, unsigned int from, unsigned int to);
bool has_edge(graph *graph, unsigned int from, unsigned int to);


#endif