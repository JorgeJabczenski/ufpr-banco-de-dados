/**
 * @file  main.cpp
 * @brief Arquivo principal com a solução do software.
 * @date 13/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

// #define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(str)                        \
    do                                          \
    {                                           \
        std::cout << "[DEBUG] " << str << endl; \
    } while (false);
#else
#define DEBUG_PRINT(str) \
    do                 \
    {                  \
    } while (false)
#endif

/*---------------------------------------------------------------------------*/
/*                              DATA STRUCTURES                              */
/*---------------------------------------------------------------------------*/

/** @struct input_t
 *  @brief Estrutura para armazenar dados de uma entrada
 *  @var input_t::time
 *      Tempo de entrada da operacao
 *  @var input_t::id
 *      Identificador da transação
 *  @var input_t::op
 *      Tipo de operação realizada durante a transação (R, W ,C)
 *  @var input_t::attr
 *      Atributo operado na operação
 */
typedef struct
{
    int time;  // time of execution
    int id;    // transaction id
    char op;   // operation (R,W,C)
    char attr; // attribute
} input_t;

typedef struct
{
    int time;
    int op;
    int attr;
} command_t;

typedef struct
{
    int id;
    int commit_time;
    list<input_t> commands;
    list<char> attrs;
} transaction_t;

typedef struct
{
    int id;
    list<transaction_t> transactions;
    list<input_t> inputs;
    transaction_t last_write;
} scheduling_t;

/** @struct output_t
 *  @brief Estrutura para armazenar dados da saida
 *  @var output_t::time
 *      Tempo de saida
 *  @var output_t::transaction_ids
 *      Ids das transactions daquele agendamento 
 *  @var output_t::serializable
 *      Indica se o agendamento é serializável
 *  @var output_t::equivalent
 *      Indica se o agendamento é equivalente por visão 
 */
typedef struct
{
    int time;
    list<int> transactions_ids;
    bool serializable;
    bool equivalent;
} output_t;

/*---------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                */
/*---------------------------------------------------------------------------*/
/*-----------------------------------*/
/*              PARSES               */
/*-----------------------------------*/

input_t parse_string_to_input(string line)
{
    input_t in;
    int size = line.size();
    char input_array[size];
    for (int i = 0; i < size; i++)
        input_array[i] = line[i];
    sscanf(input_array, "%d %d %c %c", &in.time, &in.id, &in.op, &in.attr);
    return in;
}

list<transaction_t> parse_to_transaction_list(list<input_t> input_list)
{
    list<transaction_t> transaction_list;
    int transaction_qtd = 0;
    list<int> transactions_id_list;

    // find the quantity of transactions
    for (input_t in : input_list)
    {
        bool found = (std::find(transactions_id_list.begin(), transactions_id_list.end(), in.id) != transactions_id_list.end());
        if (!found)
            transactions_id_list.push_back(in.id);
    }
    DEBUG_PRINT(transactions_id_list.size());

    transaction_t transaction_array[transactions_id_list.size()];
    // update transactions ids on array
    for (int i = 0; i < transactions_id_list.size(); i++)
        transaction_array[i].id = i+1;
    
    for (input_t in : input_list)
    {
        // add the operation to the transaction
        transaction_array[in.id-1].commands.push_back(in);
        
        // if it was a commit, update the transaction commit time
        if (in.op == 'C')
            transaction_array[in.id-1].commit_time = in.time;
        
        // update transaction attribute list 
        bool found = (std::find(transaction_array[in.id-1].attrs.begin(), transaction_array[in.id-1].attrs.end(), in.attr) != transaction_array[in.id-1].attrs.end());
        if (!found && in.attr != '-')
            transaction_array[in.id-1].attrs.push_back(in.attr);
    }

    // convert transaction array to transaction list
    for (int i = 0 ; i < transactions_id_list.size(); i++)
        transaction_list.push_back(transaction_array[i]);

    return transaction_list;
}

/*-----------------------------------*/
/*              PRINTS               */
/*-----------------------------------*/

void print_int_list(list<int> l, bool jump_line)
{
    for(int item : l)
        cout << item << " ";
    cout << ((jump_line) ? "\n" : " ");
}

void print_char_list(list<char> l, bool jump_line)
{
    for(char item : l)
        cout << item << " ";
    cout << ((jump_line) ? "\n" : " ");
}

void print_input(input_t input)
{
    // cout << "--------------" << endl;
    cout << "  time  : " << input.time << endl;
    cout << "  id    : " << input.id << endl;
    cout << "  op    : " << input.op << endl;
    cout << "  attr  : " << input.attr << endl;
    // cout << "--------------" << endl;
    cout << endl;
}

void print_output(output_t output)
{
    cout << output.time << " ";
    print_int_list(output.transactions_ids, false);
    cout << (output.serializable ? "SS" : "NS") << " ";
    cout << (output.equivalent   ? "SV" : "NV");
    cout << endl;
}

void print_transaction(transaction_t t)
{ 
    cout << "ID : " << t.id << endl;
    cout << "Commands" << endl;
    for (input_t c : t.commands)
        print_input(c);
    cout << "Attrs" << endl;
    cout << "  ";
    print_char_list(t.attrs, true);
    cout << "C Time : " << t.commit_time;
    cout << endl;
    cout <<"-------------------------";
    cout << endl;
}

/*-----------------------------------*/
/*              ------               */
/*-----------------------------------*/

list<input_t> read_inputs()
{
    list<input_t> input_list;
    string line;
    while (getline(cin, line))
    {
        input_list.push_back(parse_string_to_input(line));
    }
    return input_list;
}

/*---------------------------------------------------------------------------*/
/*                                   MAIN                                    */
/*---------------------------------------------------------------------------*/

int main()
{
    // read all inputs
    list<input_t> input_list;
    input_list = read_inputs();

    #ifdef DEBUG
    for (input_t in : input_list)
        print_input(in);
    #endif

    // parse inputs into transactions
    list<transaction_t> transactions_list;
    transactions_list = parse_to_transaction_list(input_list);

    for (transaction_t t : transactions_list){
        print_transaction(t);
    }

}