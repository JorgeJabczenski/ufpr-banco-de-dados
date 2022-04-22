/**
 * @file  transactions.h
 * @brief Arquivo com os cabeçalhos das funções de transactions.cpp
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#ifndef __TRANSACTIONS__
#define __TRANSACTIONS__
#include "utils.h"

/**
 * @param vector<input_t> inputs
 * @param int qtd_vertices
 * @brief Testa a seriabilidade das entradas
 * @return Retorna se é serializável por conflito
 */
bool is_conflict_serializable(vector<input_t> inputs, int qtd_vertices);

/**
 * @param vector<input_t> inputs
 * @brief Testa a equivalencia por visão de um agendamento
 * @return Retorna se é equivalente por visão
 */
bool is_view_equivalent(vector<input_t> inputs);

/**
 * @param vector<input_t> inputs
 * @brief Encontra a última escrita em um vetor de entradas
 * @return Map com o atributo e id da transação.
 */
last_write find_last_write(vector<input_t> inputs);

/**
 * @param vector<input_t> inputs
 * @brief Encontra as operacoes de escrita, e também sua relação com as operações de leitura
 * @return Map com as relações de leitura e escrita
 */
writes find_writes(vector<input_t> inputs);

/**
 * @param vector<schedule_t> schedules
 * @param int vertices
 * @brief Processa o vetor de agendamentos utilizando os algoritmos
 * de visão equivalente e serialidade por conflito
 * @return Imprime na saída padrão o resultado do processamento
 */
void process_inputs(vector<schedule_t> schedules, int vertices);

#endif