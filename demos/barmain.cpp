#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>
#include <set>

double t = 0;
bool a(double &x, double &y)
{
    t += .1;

    x = 10 * sin(t);
    y = 10 * cos(t);

    if (t < 7)
        return true;
    else
    {
        t = 0;
        return false;
    }
}

int main()
{
    set<SDL_Keycode> keys;

    BarGraph g;
    cout << g << '\n';

    g.equations.push_back(a);
    g.colors.push_back(makeColor(255, 0, 0, 255));

    SDL_Event event;
    bool isRunning = true;

    while (isRunning)
    {
        g.refresh(false);

        g.writer->write(jgraph::TITLE, 0, 0, makeColor(0, 0, 0, 255));

        SDL_RenderPresent(g.rend);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == 27)
                    isRunning = false;
                if (event.key.keysym.sym == 's')
                {
                    g.screenShot("bar.bmp");
                    cout << "Screenshot taken.\n";
                }
                if (event.key.keysym.sym == 'c')
                {
                    g.csv("bar.csv");
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
