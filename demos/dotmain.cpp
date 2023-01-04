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
    jgraph::FONT_PATH = "/usr/include/jgraph/fonts/Open_Sans/static/OpenSans/OpenSans-Bold.ttf";
    jgraph::WIDTH = jgraph::HEIGHT = 512;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 1;
    jgraph::FONT_POINTS = 24 / jgraph::UPSCALING_X;
    jgraph::TITLE = "DotMain";

    DotGraph g;
    cout << g << '\n';

    g.equations.push_back(s);
    g.equations.push_back(c);

    mainLoop(&g);

    return 0;
}
