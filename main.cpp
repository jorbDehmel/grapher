#include "slopefield.hpp"

#include <iostream>
#include <cmath>
#include <set>

double dy(double &x, double &y)
{
    return x + y;
}

int main()
{
    set<SDL_Keycode> keys;
    SlopeField g;

    g.equations.push_back(dy);

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
                // cout << event.key.keysym.sym << '\n';
                break;
            default:
                keys.erase(event.key.keysym.sym);
                break;
            }
        }

        /*if (keys.count(1073741906) != 0)
            yOffset += 1;
        else if (keys.count(1073741904) != 0)
            xOffset -= 1;
        else if (keys.count(1073741905) != 0)
            yOffset -= 1;
        else if (keys.count(1073741903) != 0)
            xOffset += 1;
        */
    }

    return 0;
}
