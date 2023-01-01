#include "graph.hpp"

//////////////////////////////

namespace graph
{
    unsigned int HEIGHT = 256, WIDTH = 256;
    double UPSCALING_X = 4, UPSCALING_Y = 4;
    char TITLE[64] = "Jorb Grapher 0.01";

    bool SDL_IS_INITIALIZED = false;
}

using namespace graph;

//////////////////////////////

SDL_Color makeColor(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a)
{
    SDL_Color out;
    out.r = r;
    out.g = g;
    out.b = b;
    out.a = a;

    return out;
}

//////////////////////////////

Graph::Graph()
{
    bgc.r = bgc.g = bgc.b = bgc.a = 255;

    xMin = yMin = -10;
    xMax = yMax = 10;

    if (!SDL_IS_INITIALIZED)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_IS_INITIALIZED = true;
    }

    wind = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    rend = SDL_CreateRenderer(wind, 0, 1);
    SDL_SetWindowSize(wind, WIDTH * UPSCALING_X, HEIGHT * UPSCALING_Y);
    SDL_RenderSetScale(rend, UPSCALING_X, UPSCALING_Y);

    return;
}

Graph::~Graph()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);

    SDL_Quit();

    SDL_IS_INITIALIZED = false;

    return;
}

void Graph::convertPoint(const double &xIn, const double &yIn, double &xOut, double &yOut)
{
    xOut = ((xIn - xMin) / (xMax - xMin)) * WIDTH;
    yOut = ((yIn - yMax) / (yMin - yMax)) * HEIGHT;

    return;
}

void Graph::refresh()
{
    SDL_SetRenderDrawColor(rend, bgc.r, bgc.g, bgc.b, bgc.a);
    SDL_RenderClear(rend);

    // Draw axii
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawLineF(rend, (-xMin / (xMax - xMin)) * WIDTH, 0, (-xMin / (xMax - xMin)) * WIDTH, HEIGHT);
    SDL_RenderDrawLineF(rend, 0, (-yMax / (yMin - yMax)) * HEIGHT, WIDTH, (-yMax / (yMin - yMax)) * HEIGHT);

    return;
}

//////////////////////////////

void DotGraph::refresh()
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    for (int i = 0; i < equations.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            convertPoint(x, y, realX, realY);
            SDL_RenderDrawPoint(rend, realX, realY);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation modifies x.");
        }
    }

    SDL_RenderPresent(rend);

    return;
}

//////////////////////////////

void LineGraph::refresh()
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    vector<vector<SDL_Point>> points;

    // Prepare data
    for (int i = 0; i < equations.size(); i++)
    {
        vector<SDL_Point> eqData;

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            convertPoint(x, y, realX, realY);

            // Log point
            SDL_Point temp;
            temp.x = realX;
            temp.y = realY;

            eqData.push_back(temp);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation is bounded.");
        }

        points.push_back(eqData);
    }

    // Graph data
    for (int i = 0; i < points.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (int j = 0; j + 1 < points[i].size(); j++)
        {
            SDL_Point a = points[i][j], b = points[i][j + 1];

            SDL_RenderDrawLineF(rend, a.x, a.y, b.x, b.y);
        }
    }

    SDL_RenderPresent(rend);

    return;
}

//////////////////////////////

void BarGraph::refresh()
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    vector<vector<SDL_Point>> points;

    // Prepare data
    for (int i = 0; i < equations.size(); i++)
    {
        vector<SDL_Point> eqData;

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            convertPoint(x, y, realX, realY);

            // Log point
            SDL_Point temp;
            temp.x = realX;
            temp.y = realY;

            eqData.push_back(temp);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation is bounded.");
        }

        points.push_back(eqData);
    }

    // Graph data
    for (int i = 0; i < points.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (int j = 0; j + 1 < points[i].size(); j++)
        {
            SDL_Point a = points[i][j], b = points[i][j + 1];

            SDL_Rect r;

            r.x = a.x;
            r.y = (-yMax / (yMin - yMax)) * HEIGHT;

            r.w = b.x - a.x;
            r.h = a.y - (-yMax / (yMin - yMax)) * HEIGHT;

            SDL_RenderFillRect(rend, &r);
        }
    }

    SDL_RenderPresent(rend);

    return;
}
