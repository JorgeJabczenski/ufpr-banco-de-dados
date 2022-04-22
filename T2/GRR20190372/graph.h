/**
 * @file  graph.h
 * @brief Arquivo com os cabeçalhos das funções de graph.cpp
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/
 
#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <vector>

/** @struct graph_t
 *  @brief Estrutura que representa um grafo
 *  @var graph_t::matrix
 *      Matriz de adjacência
 *  @var graph_t::qtd_vertices
 *      Número de vértices
 */
typedef struct {
   int qtd_vertices; 
	std::vector<std::vector<int>> matrix;
} graph_t;


/**  
 * @param int qtd_vertices (Número de vértices do grafo)
 * @brief Inicializa um grafo
 * @return graph_t* inicializado
 */
graph_t* init_graph(int qtd_vertices);

/**
 * @param graph_t* graph
 * @param int i
 * @param int j
 * @brief Insere aresta em um grafo.
 * o é a origem e d o destino
 */
void insert_edge(graph_t* graph, int o, int d);

/**
 * @param graph_t* graph
 * @param vector<bool> reads
 * @param int index
 * @brief Função auxiliar para procurar ciclos em grafos.
 * @return Retorna se encontrou um ciclo
 */
bool find_cycle_aux(graph_t* graph, std::vector<bool> reads, int index);

/**
 * @param graph_t* graph
 * @brief Procura um ciclo em um grafo.
 * @return Retorna se encontrou um ciclo
 */
bool find_cycle(graph_t* graph);

#endif 