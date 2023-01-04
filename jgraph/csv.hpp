#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <string>
#include <vector>
using namespace std;

template <class T>
struct CSV
{
    vector<string> names;
    vector<vector<T> *> data;
};

CSV<double> loadVerticalCSVF(const char *path);
CSV<double> loadHorizontalCSVF(const char *path);

CSV<string> loadVerticalCSV(const char *path);
CSV<string> loadHorizontalCSV(const char *path);

#endif
