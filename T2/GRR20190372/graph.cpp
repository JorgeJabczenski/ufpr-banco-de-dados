/**
 * @file  graph.cpp
 * @brief Arquivo com as implementações das funções de grafos
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#include "graph.h"
using namespace std;

graph_t *init_graph(int qtd_vertices)
{

	graph_t *graph = new graph_t;
	graph->qtd_vertices = qtd_vertices;
	vector<int> line(qtd_vertices, 0);

	for (int i = 0; i < qtd_vertices; ++i)
		graph->matrix.push_back(line);

	return graph;
}

void insert_edge(graph_t *graph, int o, int d)
{
	graph->matrix[o][d] = 1;
}

bool find_cycle_aux(graph_t *graph, vector<bool> reads, int index)
{

	if (reads[index])
		return true;

	reads[index] = true;
	bool cycle = false;
	for (int i = 0; i < graph->qtd_vertices; ++i)
	{
		if (graph->matrix[index][i] == 1)
		{
			cycle = find_cycle_aux(graph, reads, i);
			if (cycle)
			{
				reads[index] = false;
				return true;
			}
		}
	}
	reads[index] = false;
	return false;
}

bool find_cycle(graph_t *graph)
{

	vector<bool> reads(graph->qtd_vertices, 0);
	bool cycle = false;

	for (int i = 0; i < graph->qtd_vertices; ++i)
	{
		reads[i] = true;
		for (int j = 0; j < graph->qtd_vertices; ++j)
		{
			if (graph->matrix[i][j] == 1)
			{
				cycle = find_cycle_aux(graph, reads, j);
				if (cycle)
					return true;
			}
		}
		reads[i] = false;
	}
	return false;
}
