#include "quinemccluskey.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(void)
{
    string truth_table_rows("000010001X1110X1"); // wikipedia example

    vector<string> var_names;
    var_names.push_back("a");
    var_names.push_back("b");
    var_names.push_back("c");
    var_names.push_back("d");

    cout << Get_SOP_Expression_String(truth_table_rows, var_names) << endl;
    cout << Get_POS_Expression_String(truth_table_rows, var_names) << endl;

    cin.sync();
    cin.get();

    return 0;
}
