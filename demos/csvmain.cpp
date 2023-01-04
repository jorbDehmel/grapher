#include "../jgraph/csv.hpp"
#include <iostream>
using namespace std;

int main()
{
    auto results = loadVerticalCSVF("csv.csv");

    for (int i = 0; i < results.names.size(); i++)
    {
        cout << results.names[i] << '\n';
        for (auto d : *results.data[i])
        {
            cout << '\t' << d << '\n';
        }
    }

    cout << "\nFILE 2\n\n";

    results = loadHorizontalCSVF("hor.csv");

    for (int i = 0; i < results.names.size(); i++)
    {
        cout << results.names[i] << '\n';
        for (auto d : *results.data[i])
        {
            cout << '\t' << d << '\n';
        }
    }

    return 0;
}
