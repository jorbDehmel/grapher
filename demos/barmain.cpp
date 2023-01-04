#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>

bool a(double &x, double &y)
{
    y = 10 * sin(x);
    x += .1;

    return true;
}

int main()
{
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 4;
    jgraph::TITLE = "BarGraph";

    BarGraph g;
    cout << g << '\n';

    g.equations.push_back(a);
    g.colors.push_back(makeColor(255, 0, 0, 255));

    mainLoop(&g);

    return 0;
}
