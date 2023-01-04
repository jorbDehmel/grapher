#include <jgraph/jgraph.hpp>
#include <iostream>
using namespace std;

double dy(const double x, const double y)
{
    return pow(abs(x), y);
}

int main()
{
    jgraph::FONT_PATH = "/usr/include/jgraph/fonts/Open_Sans/static/OpenSans/OpenSans-Bold.ttf";
    jgraph::FONT_POINTS = 24;
    jgraph::WIDTH = jgraph::HEIGHT = 1028;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 1;
    jgraph::TICK_SPACING_X = jgraph::TICK_SPACING_Y = .1;

    GradientField g(dy);
    cout << g << '\n';

    mainLoop(&g);

    return 0;
}
