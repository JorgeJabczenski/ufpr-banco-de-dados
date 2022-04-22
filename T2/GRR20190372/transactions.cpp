/**
 * @file  transactions.cpp
 * @brief Arquivo com as implementações de escalonamento
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#include "transactions.h"
#include <algorithm>

bool is_conflict_serializable(vector<input_t> inputs, int qtd_vertices)
{
    graph_t *graph = init_graph(qtd_vertices);
    int size = inputs.size();

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if ((inputs[i].id != inputs[j].id) && (inputs[i].attr == inputs[j].attr))
            {
                if ((inputs[i].op == 'W') && (inputs[j].op == 'W'))
                    insert_edge(graph, inputs[i].id - 1, inputs[j].id - 1);

                if ((inputs[i].op == 'W') && (inputs[j].op == 'R'))
                    insert_edge(graph, inputs[i].id - 1, inputs[j].id - 1);

                if ((inputs[i].op == 'R') && (inputs[j].op == 'W'))
                    insert_edge(graph, inputs[i].id - 1, inputs[j].id - 1);
            }
        }
    }
    return !find_cycle(graph);
}

static unsigned long long factorial(int valor)
{
    unsigned long long factorial = 1;

    for (int i = 1; i <= valor; i++)
        factorial *= i;

    return factorial;
}

static vector<int> get_ids(vector<input_t> inputs)
{
    vector<int> id_list(inputs.size());
    int size = inputs.size();

    for (int i = 0; i < size; i++)
        id_list[i] = inputs[i].id;

    sort(id_list.begin(), id_list.end());
    vector<int>::iterator iter;
    iter = unique(id_list.begin(), id_list.end());
    id_list.resize(distance(id_list.begin(), iter));

    return id_list;
}

last_write find_last_write(vector<input_t> inputs)
{
    last_write last;

    for (int i = inputs.size() - 1; i >= 0; i--)
        if ((inputs[i].op == 'W') && (!last.count(inputs[i].attr)))
            last.insert(make_pair(inputs[i].attr, inputs[i].id));

    return last;
}

writes find_writes(vector<input_t> inputs)
{
    writes wr;

    for (int i = inputs.size() - 1; i >= 0; i--)
    {
        if ((inputs[i].op == 'R'))
        {
            key temp_key;

            temp_key = make_pair(make_pair(inputs[i].order, inputs[i].id), inputs[i].attr);
            int j = i - 1;

            while (j >= 0)
            {
                if ((inputs[i].attr == inputs[j].attr) && (inputs[j].op == 'W'))
                {
                    wr.insert(make_pair(temp_key, make_pair(inputs[j].id, inputs[j].order)));
                }
                j--;
            }

            if (wr.find(temp_key) == wr.end())
                wr.insert(make_pair(temp_key, make_pair(0, 0)));
        }
    }
    return wr;
}

bool is_view_equivalent(vector<input_t> inputs)
{
    vector<int> ids(inputs.size());
    last_write final_write;
    writes other_writes;
    bool equivalent;
    unsigned long long fatorial;

    ids = get_ids(inputs);
    final_write = find_last_write(inputs);
    other_writes = find_writes(inputs);
    fatorial = factorial(ids.size());

    for (unsigned long long i = 0; i < fatorial; i++)
    {
        equivalent = true;
        vector<input_t> view;
        int ids_size = ids.size();
        int input_size = inputs.size();

        for (int j = 0; j < ids_size; j++)
            for (int k = 0; k < input_size; k++)
                if (inputs[k].id == ids[j])
                    view.push_back(inputs[k]);

        last_write view_final_write = find_last_write(view);

        for (last_write::iterator it = final_write.begin(); it != final_write.end(); it++)
        {
            last_write::iterator it_operacoes = view_final_write.find(it->first);

            if ((it->first != it_operacoes->first) || (it->second != it_operacoes->second))
                equivalent = false;
        }

        writes other_view_writes = find_writes(view);

        for (writes::iterator it = other_writes.begin(); it != other_writes.end(); it++)
        {
            writes::iterator it_operacoes = other_view_writes.find(it->first);

            if ((it->first != it_operacoes->first) || (it->second != it_operacoes->second))
                equivalent = false;
        }

        if (equivalent)
            return equivalent;

        next_permutation(ids.begin(), ids.end());
    }

    return equivalent;
}

void process_inputs(vector<schedule_t> schedules, int vertices)
{
    int sched_size = schedules.size();
    for (int i = 0; i < sched_size; ++i)
    {
        printf("%d ", i + 1);

        for (int j = 0; j < schedules[i].qtd_transactions; j++)
            printf("%d%c", schedules[i].id_vector[j], j + 1 >= schedules[i].qtd_transactions ? ' ' : ',');

        if (is_conflict_serializable(schedules[i].inputs, vertices))
            printf("SS ");
        else
            printf("NS ");

        if (is_view_equivalent(schedules[i].inputs))
            printf("SV");
        else
            printf("NV");

        printf("\n");
    }
}