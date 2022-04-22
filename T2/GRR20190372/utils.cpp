/**
 * @file  utils.cpp
 * @brief Arquivo com as implementações de utils.
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#include "utils.h"
#include <algorithm>

using namespace std;

vector<input_t> read_inputs(int *v)
{
    int qtd_read = 0;
    vector<input_t> inputs;
    input_t *in = new input_t;

    do
    {
        qtd_read = scanf("%d %d %c %c\n", &in->order, &in->id, &in->op, &in->attr);
        inputs.push_back(*in);

        if (in->id > (*v))
            (*v) = in->id;

    } while (qtd_read == 4);

    inputs.pop_back();

    return inputs;
}

static vector<int> create_id_vector(vector<int> vetor)
{
    int vetor_size = vetor.size();
    vector<int> output(vetor_size, 0);
    int qtd = 0;

    for (int i = 1; i < vetor_size; i++)
        if (vetor[i] == 1)
            output[qtd++] = i;

    output.resize(qtd);
    sort(output.begin(), output.end());
    return output;
}

vector<schedule_t> parse_inputs_to_schedule_list(vector<input_t> inputs)
{
    int count_commits = 0, running = 0, i = 0, j = 0;
    vector<schedule_t> schedule_list;
    vector<bool> vetor(inputs.size(), 0);
    vector<int> vetor_aux(inputs.size(), 0);

    int inputs_size = inputs.size();
    while (i < inputs_size)
    {
        schedule_t *sched = new schedule_t;
        sched->qtd_inputs = 0;
        sched->qtd_transactions = 0;

        int v_aux_size = vetor_aux.size();
        for (int k = 0; k < v_aux_size; k++)
            vetor_aux[k] = 0;

        do
        {
            sched->inputs.push_back(inputs[i]);
            sched->qtd_inputs++;

            if ((vetor[inputs[i].id] != 1) && (inputs[i].op != 'C'))
            {
                vetor[inputs[i].id] = 1;
                vetor_aux[inputs[i].id] = 1;
                running++;
                sched->qtd_transactions++;
            }

            if ((vetor[inputs[i].id] == 1) && (inputs[i].op == 'C'))
            {
                vetor[inputs[i].id] = 0;
                running--;
            }

            i++;

        } while ((running != 0) && (i < inputs_size));

        schedule_list.push_back(*sched);

        schedule_list[j].id_vector = create_id_vector(vetor_aux);

        j++;

        int v_size = vetor.size();
        for (int k = 0; k < v_size; k++)
            count_commits += vetor[k];

        if (count_commits != 0)
        {
            perror("Houve uma transação que não executou o commit");
            exit(-1);
        }
    }

    return schedule_list;
}
