/**
 * @file  escalona.cpp
 * @brief Arquivo principal
 * @date 22/04/2022
 * @author GRR20190372 - Jorge Lucas Vicilli Jabczenski
 **/

#include "transactions.h"

using namespace std;

int main()
{
    vector<input_t> input_vector;
    vector<schedule_t> schedules;
    int vertices = 0;

    input_vector = read_inputs(&vertices);

    schedules = parse_inputs_to_schedule_list(input_vector);

    process_inputs(schedules, vertices);

    return 0;
}
