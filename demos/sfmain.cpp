#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>
#include <set>

double dy(const double x, const double y)
{
    return x + y;
}

int main()
{
    set<SDL_Keycode> keys;
    SlopeField g;
    cout << g << '\n';

    g.equations.push_back(dy);

    g.colors.push_back(makeColor(255, 0, 0, 255));

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
                if (event.key.keysym.sym == 's')
                    g.screenShot("screenshot.bmp");
                keys.insert(event.key.keysym.sym);
                break;
            default:
                keys.erase(event.key.keysym.sym);
                break;
            }
        }
    }

    return 0;
}
