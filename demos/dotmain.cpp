#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>

bool c(double &x, double &y)
{
    x += .01;
    y = 10 * cos(x);

    return true;
}

bool s(double &x, double &y)
{
    x += .01;
    y = 10 * sin(x);

    return true;
}

int main()
{
    jgraph::WIDTH = jgraph::HEIGHT = 512;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 2;

    DotGraph g;
    cout << g << '\n';

    g.equations.push_back(s);
    g.equations.push_back(c);

    g.colors.push_back(makeColor(255, 0, 0, 255));
    g.colors.push_back(makeColor(0, 0, 255, 255));

    mainLoop(&g);

    return 0;
}
