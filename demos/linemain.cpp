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

    jgraph::FONT_PATH = "/usr/include/jgraph/fonts/Open_Sans/static/OpenSans/OpenSans-Bold.ttf";
    jgraph::WIDTH = jgraph::HEIGHT = 1028;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 1;
    jgraph::FONT_POINTS = 24 / jgraph::UPSCALING_X;
    jgraph::TITLE = "LineGraph";

    LineGraph g;
    cout << g << '\n';

    g.equations.push_back(a);

    mainLoop(&g);

    return 0;
}
