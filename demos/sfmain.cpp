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
    jgraph::TITLE = "SlopeFieldGraph";

    SlopeField g;
    cout << g << '\n';

    g.equations.push_back(dy);
    g.colors.push_back(makeColor(255, 0, 0, 255));

    mainLoop(&g);

    return 0;
}
