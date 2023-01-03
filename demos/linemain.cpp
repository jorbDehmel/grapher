#include <jgraph/jgraph.hpp>

#include <iostream>

vector<double> xList;
vector<double> yList;

int pos = 0;
bool a(double &x, double &y)
{
    x = xList[pos];
    y = yList[pos];
    pos++;

    if (pos > xList.size())
    {
        pos = 0;
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    xList.push_back(-8);
    yList.push_back(8);

    xList.push_back(9);
    yList.push_back(-1);

    xList.push_back(0);
    yList.push_back(4);

    xList.push_back(-2);
    yList.push_back(9);

    xList.push_back(-2);
    yList.push_back(-9);

    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 4;

    LineGraph g;
    cout << g << '\n';

    g.equations.push_back(a);
    g.colors.push_back(makeColor(255, 0, 0, 255));

    mainLoop(&g);

    return 0;
}
