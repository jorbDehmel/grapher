#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>
#include <set>

bool a(double &x, double &y)
{
    x += .01;
    y = 10 * cos(x);

    return true;
}

int main()
{
    set<SDL_Keycode> keys;

    DotGraph g;
    cout << g << '\n';

    g.equations.push_back(a);

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
                {
                    g.screenShot("dot.bmp");
                    cout << "Screenshot taken.\n";
                }
                if (event.key.keysym.sym == 'c')
                {
                    g.csv("dot.csv");
                    cout << "CSV saved.\n";
                }

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
