/**
 * @file  utils.h
 * @brief Arquivo com os cabeçalhos das funções de utils.cpp
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#ifndef __UTILS__
#define __UTILS__

#include "graph.h"
#include <map>

using namespace std;

/** @struct input_t
 *  @brief Estrutura para armazenar dados de uma operacao
 *  @var input_t::order
 *      Tempo de entrada da operacao
 *  @var input_t::id
 *      Identificador da transação
 *  @var input_t::op
 *      Tipo de operação
 *  @var input_t::attr
 *      Atributo utilizado na operação
 */
typedef struct
{
    int order;
    int id;
    char op;
    char attr;
} input_t;

/** @struct schedule_t
 *  @brief Estrutura que guarda os dados de um agendamento
 *  @var schedule_t::id_vector
 *      Vetor de ids das transações daquele agendamento
 *  @var schedule_t::qtd_transactions
 *      Quantidade de transações
 *  @var schedule_t::inputs
 *      Vetor de operações daquele agendamento
 *  @var schedule_t::qtd_inputs
 *      Número de operações
 */
typedef struct
{
    int qtd_transactions;
    int qtd_inputs;
    vector<int> id_vector;
    vector<input_t> inputs;
} schedule_t;

/** @type pair<pair<int,int>,char>
 *  @brief Chave de uma escrita
 */
typedef pair<pair<int, int>, char> key;

/** @type map<key,pair<int,int>>
 *  @brief Mapa para uma escrita
 */
typedef map<key, pair<int, int>> writes;

/** @type map<char, int>
 *  @brief Mapeamento de uma operacao para uma transacao de ultima escrita
 */
typedef map<char, int> last_write;

/**
 * @param int *v (id da transacao mais nova)
 * @brief Separa e armazena as entradas em um vetor
 * @return Um vetor com as entradas
 */
vector<input_t> read_inputs(int *v);

/** @param vector<input_t> entradas
 *  @brief Separa as entradas em uma lista de agendamentos individuais
 *  @return Um vetor de agendamentos
 */
vector<schedule_t> parse_inputs_to_schedule_list(vector<input_t> entradas);

#endif