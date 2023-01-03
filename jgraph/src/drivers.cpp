#include "../drivers.hpp"

void mainLoop(BarGraph *g)
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        g->refresh();

        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == 27)
                isRunning = false;
            else if (event.key.keysym.sym == 's')
            {
                string path = jgraph::TITLE;
                path += ".bmp";
                g->screenshot(path.c_str());
            }
            else if (event.key.keysym.sym == 'c')
            {
                string path = jgraph::TITLE;
                path += ".csv";
                g->csv(path.c_str());
            }
        }
    }

    return;
}

void mainLoop(BarGraph *g, void (*update)(BarGraph *graph, set<int> &pressedKeys))
{
    bool isRunning = true;
    SDL_Event event;
    set<int> keys;

    while (isRunning)
    {
        g->refresh(false);

        update(g, keys);

        SDL_RenderPresent(g->rend);

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            keys.insert(event.key.keysym.sym);
        case SDL_KEYUP:
            keys.erase(event.key.keysym.sym);
        }
    }

    return;
}

void mainLoop(DotGraph *g)
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        g->refresh();

        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == 27)
                isRunning = false;
            else if (event.key.keysym.sym == 's')
            {
                string path = jgraph::TITLE;
                path += ".bmp";
                g->screenshot(path.c_str());
            }
            else if (event.key.keysym.sym == 'c')
            {
                string path = jgraph::TITLE;
                path += ".csv";
                g->csv(path.c_str());
            }
        }
    }

    return;
}

void mainLoop(DotGraph *g, void (*update)(DotGraph *graph, set<int> &pressedKeys))
{
    bool isRunning = true;
    SDL_Event event;
    set<int> keys;

    while (isRunning)
    {
        g->refresh(false);

        update(g, keys);

        SDL_RenderPresent(g->rend);

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            keys.insert(event.key.keysym.sym);
        case SDL_KEYUP:
            keys.erase(event.key.keysym.sym);
        }
    }

    return;
}

void mainLoop(LineGraph *g)
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        g->refresh();

        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == 27)
                isRunning = false;
            else if (event.key.keysym.sym == 's')
            {
                string path = jgraph::TITLE;
                path += ".bmp";
                g->screenshot(path.c_str());
            }
            else if (event.key.keysym.sym == 'c')
            {
                string path = jgraph::TITLE;
                path += ".csv";
                g->csv(path.c_str());
            }
        }
    }

    return;
}

void mainLoop(LineGraph *g, void (*update)(LineGraph *graph, set<int> &pressedKeys))
{
    bool isRunning = true;
    SDL_Event event;
    set<int> keys;

    while (isRunning)
    {
        g->refresh(false);

        update(g, keys);

        SDL_RenderPresent(g->rend);

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            keys.insert(event.key.keysym.sym);
        case SDL_KEYUP:
            keys.erase(event.key.keysym.sym);
        }
    }

    return;
}

void mainLoop(SlopeField *g)
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        g->refresh();

        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == 27)
                isRunning = false;
            else if (event.key.keysym.sym == 's')
            {
                string path = jgraph::TITLE;
                path += ".bmp";
                g->screenshot(path.c_str());
            }
            else if (event.key.keysym.sym == 'c')
            {
                string path = jgraph::TITLE;
                path += ".csv";
                g->csv(path.c_str());
            }
        }
    }

    return;
}

void mainLoop(SlopeField *g, void (*update)(SlopeField *graph, set<int> &pressedKeys))
{
    bool isRunning = true;
    SDL_Event event;
    set<int> keys;

    while (isRunning)
    {
        g->refresh(false);

        update(g, keys);

        SDL_RenderPresent(g->rend);

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            keys.insert(event.key.keysym.sym);
        case SDL_KEYUP:
            keys.erase(event.key.keysym.sym);
        }
    }

    return;
}

void mainLoop(GradientField *g)
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        g->refresh();

        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == 27)
                isRunning = false;
            else if (event.key.keysym.sym == 's')
            {
                string path = jgraph::TITLE;
                path += ".bmp";
                g->screenshot(path.c_str());
            }
            else if (event.key.keysym.sym == 'c')
            {
                string path = jgraph::TITLE;
                path += ".csv";
                g->csv(path.c_str());
            }
        }
    }

    return;
}

void mainLoop(GradientField *g, void (*update)(GradientField *graph, set<int> &pressedKeys))
{
    bool isRunning = true;
    SDL_Event event;
    set<int> keys;

    while (isRunning)
    {
        g->refresh(false);

        update(g, keys);

        SDL_RenderPresent(g->rend);

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            keys.insert(event.key.keysym.sym);
        case SDL_KEYUP:
            keys.erase(event.key.keysym.sym);
        }
    }

    return;
}
