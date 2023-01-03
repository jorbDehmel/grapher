#include <jgraph/jgraph.hpp>

#include <iostream>
#include <cmath>
#include <set>
#include <map>

vector<double> xList;
vector<double> yList;

int pos = 0;
bool a(double &x, double &y)
{
    x = xList[pos];
    y = yList[pos];
    pos++;

    if (pos > xList.size())
    {
        pos = 0;
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    xList.push_back(-8);
    yList.push_back(8);

    xList.push_back(9);
    yList.push_back(-1);

    xList.push_back(0);
    yList.push_back(4);

    xList.push_back(-2);
    yList.push_back(9);

    xList.push_back(-2);
    yList.push_back(-9);

    set<SDL_Keycode> keys;

    jgraph::UPSCALING_X = jgraph::UPSCALING_Y = 4;

    LineGraph g;
    cout << g << '\n';

    g.equations.push_back(a);
    g.colors.push_back(makeColor(255, 0, 0, 255));

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
