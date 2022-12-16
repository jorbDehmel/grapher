#include "graph.hpp"

#include <iostream>
#include <cmath>
#include <set>

double t = 0;

double xOffset = 0;
double yOffset = 0;

bool a(double &x, double &y)
{
    y = 5 * sin(t) + yOffset;
    x = 5 * cos(t) + xOffset;

    t += .001;

    if (t > 7)
    {
        t = 0;
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    set<SDL_Keycode> keys;
    BarGraph g;

    g.equations.push_back(a);

    g.colors.push_back(Pixel(255, 0, 0, 255));

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
                keys.insert(event.key.keysym.sym);
                cout << event.key.keysym.sym << '\n';
                break;
            default:
                keys.erase(event.key.keysym.sym);
                break;
            }
        }

        if (keys.count(1073741906) != 0)
        {
            // up
            yOffset += 1;
        }
        else if (keys.count(1073741904) != 0)
        {
            // left
            xOffset -= 1;
        }
        else if (keys.count(1073741905) != 0)
        {
            // down
            yOffset -= 1;
        }
        else if (keys.count(1073741903) != 0)
        {
            // right
            xOffset += 1;
        }
    }

    return 0;
}
