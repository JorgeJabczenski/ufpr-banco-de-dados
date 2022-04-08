#include <iostream>
#include <list>

using namespace std;

typedef struct
{
    int order;     // order of arrival 
    int id;        // transaction id
    char op;       // operation (R,W,C)
    char attr;     // attribute
} input_t;

input_t parseStringToInput(string line)
{
    line.substr(0, line.find(' '));


}

void printInput(input_t input)
{
    cout << "--------------"          << endl;   
    cout << "order : " << input.order << endl;
    cout << "id    : " << input.id    << endl;
    cout << "op    : " << input.op    << endl;
    cout << "attr  : " << input.attr  << endl;
    cout << "--------------"          << endl;
    cout << endl;
}

// void printList(list<input_t> l)
// {
//     for (int i = 0; i < l.size(); i++)
//         printInput(l)
// }



int main()
{
    list<input_t> input_list;

    string line;
    while (getline(cin, line))
    {
        input_t in = parseStringToInput(line);
        input_list.push_back(in);
        printInput(in);
    }
}