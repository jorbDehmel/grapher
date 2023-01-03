#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>
#include <set>

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
    set<SDL_Keycode> keys;

    jgraph::WIDTH = jgraph::HEIGHT = 512;
    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 2;

    DotGraph g;
    cout << g << '\n';

    g.equations.push_back(s);
    g.equations.push_back(c);

    g.colors.push_back(makeColor(255, 0, 0, 255));
    g.colors.push_back(makeColor(0, 0, 255, 255));

    SDL_Event event;
    bool isRunning = true;

    while (isRunning)
    {
        g.refresh();

        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == 27)
                isRunning = false;
            if (event.key.keysym.sym == 's')
            {
                g.screenShot("line.bmp");
                cout << "Screenshot taken.\n";
            }
            if (event.key.keysym.sym == 'c')
            {
                g.csv("line.csv");
                cout << "CSV saved.\n";
            }

            keys.insert(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            keys.erase(event.key.keysym.sym);
            break;
        }
    }

    return 0;
}
