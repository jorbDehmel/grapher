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
    jgraph::FONT_PATH = "/usr/include/jgraph/fonts/Open_Sans/static/OpenSans/OpenSans-Bold.ttf";
    jgraph::WIDTH = jgraph::HEIGHT = 512;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 1;
    jgraph::FONT_POINTS = 24 / jgraph::UPSCALING_X;
    jgraph::TITLE = "BarGraph";

    BarGraph g;
    cout << g << '\n';

    g.equations.push_back(a);

    mainLoop(&g);

    return 0;
}
