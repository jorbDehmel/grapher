#include "slopefield.hpp"

void SlopeField::refresh()
{
    this->Graph::refresh();

    double realX, realY;
    double realX2, realY2;

    int steps;
    double dy;

    for (int i = 0; i < equations.size(); i++)
    {
        Pixel color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (double x = xMin; x < xMax; x++)
        {
            for (double y = yMin; y < yMax; y++)
            {
                dy = (equations[i])(x, y);

                convertPoint(x, y, realX, realY);
                convertPoint(x + .5, y + (dy * .5), realX2, realY2);

                SDL_RenderDrawLine(rend, realX, realY, realX2, realY2);
            }
        }
    }

    SDL_RenderPresent(rend);

    return;
}
