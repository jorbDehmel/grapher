#include "../csv.hpp"

#include <iostream>
using namespace std;

CSV<double> loadVerticalCSVF(const char *path)
{
    ifstream in(path);
    if (!in.is_open())
    {
        throw runtime_error("Could not open file.\n");
    }

    CSV<double> out;

    // normal csv
    string line;
    getline(in, line);

    string word;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            vector<double> *toAdd = new vector<double>;
            out.data.push_back(toAdd);
            out.names.push_back(word);
            word = "";
        }
        else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            continue;
        else
        {
            word += line[i];
        }
    }
    vector<double> *toAdd = new vector<double>;
    out.data.push_back(toAdd);
    out.names.push_back(word);
    word = "";

    while (getline(in, line))
    {
        int row = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                if (row < out.data.size())
                {
                    out.data[row]->push_back(stod(word));
                }
                else
                {
                    in.close();
                    throw runtime_error("Invalidly formatted file; cannot parse");
                }

                word = "";
                row++;
            }
            else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            {
                word += line[i];
            }
        }
        out.data[row]->push_back(stod(word));
        word = "";
    }

    in.close();

    return out;
}

CSV<double> loadHorizontalCSVF(const char *path)
{
    ifstream in(path);
    if (!in.is_open())
    {
        throw runtime_error("Could not open file.\n");
    }

    CSV<double> out;

    string line;
    int lineNum = 0;
    while (getline(in, line))
    {
        int i = 0;

        string word;
        while (i < line.size() && line[i] != ',')
        {
            word += line[i];
            i++;
        }

        out.names.push_back(word);
        word = "";

        vector<double> *toAdd = new vector<double>;
        out.data.push_back(toAdd);

        while (i < line.size())
        {
            i++;

            if (line[i] == ',')
            {
                out.data[lineNum]->push_back(stod(word));
                word = "";
            }
            else if (i != ' ')
            {
                word += line[i];
            }
        }
        out.data[lineNum]->push_back(stod(word));
        word = "";

        lineNum++;
    }

    in.close();

    return out;
}

CSV<string> loadVerticalCSV(const char *path)
{
    ifstream in(path);
    if (!in.is_open())
    {
        throw runtime_error("Could not open file.\n");
    }

    CSV<string> out;

    // normal csv
    string line;
    getline(in, line);

    string word;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            vector<string> *toAdd = new vector<string>;
            out.data.push_back(toAdd);
            out.names.push_back(word);
            word = "";
        }
        else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            continue;
        else
        {
            word += line[i];
        }
    }
    vector<string> *toAdd = new vector<string>;
    out.data.push_back(toAdd);
    out.names.push_back(word);
    word = "";

    while (getline(in, line))
    {
        int row = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                if (row < out.data.size())
                {
                    out.data[row]->push_back(word);
                }
                else
                {
                    in.close();
                    throw runtime_error("Invalidly formatted file; cannot parse");
                }

                word = "";
                row++;
            }
            else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            {
                word += line[i];
            }
        }
        out.data[row]->push_back(word);
        word = "";
    }

    in.close();

    return out;
}

CSV<string> loadHorizontalCSV(const char *path)
{
    ifstream in(path);
    if (!in.is_open())
    {
        throw runtime_error("Could not open file.\n");
    }

    CSV<string> out;

    string line;
    int lineNum = 0;
    while (getline(in, line))
    {
        int i = 0;

        string word;
        while (i < line.size() && line[i] != ',')
        {
            word += line[i];
            i++;
        }

        out.names.push_back(word);
        word = "";

        vector<string> *toAdd = new vector<string>;
        out.data.push_back(toAdd);

        while (i < line.size())
        {
            i++;

            if (line[i] == ',')
            {
                out.data[lineNum]->push_back(word);
                word = "";
            }
            else if (i != ' ')
            {
                word += line[i];
            }
        }
        out.data[lineNum]->push_back(word);
        word = "";

        lineNum++;
    }

    in.close();

    return out;
}