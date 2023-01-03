#include <jgraph/jgraph.hpp>

#include <iostream>

double dy(const double x, const double y)
{
    return x * y;
}

int main()
{
    jgraph::WIDTH = jgraph::HEIGHT = 512;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 4;
    jgraph::TICK_SPACING_X = jgraph::TICK_SPACING_Y = 1;

    GradientField g;
    cout << g << '\n';

    mainLoop(&g);

    return 0;
}
