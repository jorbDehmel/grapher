#include <jgraph/jgraph.hpp>

#include <iostream>

double dy(const double x, const double y)
{
    return x * y;
}

double dy2(const double x, const double y)
{
    return x + y;
}

int main()
{
    jgraph::FONT_PATH = "/usr/include/jgraph/fonts/Open_Sans/static/OpenSans/OpenSans-Bold.ttf";
    jgraph::FONT_POINTS = 20;
    jgraph::WIDTH = jgraph::HEIGHT = 512;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 2;
    jgraph::TICK_SPACING_X = jgraph::TICK_SPACING_Y = 1;
    jgraph::TITLE = "SlopeFieldGraph";

    SlopeField g;
    cout << g << '\n';

    g.equations.push_back(dy);
    g.equations.push_back(dy2);

    mainLoop(&g);

    return 0;
}
