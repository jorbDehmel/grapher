#include "graph.hpp"

#include <iostream>
#include <cmath>

bool a(double &x, double &y)
{
    y = x;
    x += .01;

    return true;
}

int main()
{
    BarGraph g;

    g.equations.push_back(a);

    g.colors.push_back(Pixel(255, 0, 0, 255));
    // g.colors.push_back(Pixel(0, 255, 0, 255));
    // g.colors.push_back(Pixel(0, 0, 255, 255));

    SDL_Event event;
    bool isRunning = true;
    while (isRunning)
    {
        g.refresh();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == 27)
                    isRunning = false;
                break;
            default:
                break;
            }
        }

        SDL_Delay(100);
    }

    return 0;
}
