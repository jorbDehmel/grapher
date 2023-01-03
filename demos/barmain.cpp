#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>

double t = 0;
bool a(double &x, double &y)
{
    t += .1;

    x = 10 * sin(t);
    y = 10 * cos(t);

    if (t < 7)
        return true;
    else
    {
        t = 0;
        return false;
    }
}

int main()
{
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 4;

    BarGraph g;
    cout << g << '\n';

    g.equations.push_back(a);
    g.colors.push_back(makeColor(255, 0, 0, 255));

    mainLoop(&g);

    return 0;
}
