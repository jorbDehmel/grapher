#include "graph.hpp"

#include <iostream>
#include <map>

//////////////////////////////

unsigned int HEIGHT = 256, WIDTH = 256;
double UPSCALING_X = 8, UPSCALING_Y = 8;
char TITLE[64] = "Jorb Grapher 0.01";

bool SDL_IS_INITIALIZED = false;

//////////////////////////////

Graph::Graph()
{
    bgc = Pixel(255, 255, 255, 255);
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

    equations.clear();

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

void Graph::refresh()
{
    SDL_SetRenderDrawColor(rend, bgc.r, bgc.g, bgc.b, bgc.a);
    SDL_RenderClear(rend);

    // Draw axii
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawLine(rend, (-xMin / (xMax - xMin)) * WIDTH, 0, (-xMin / (xMax - xMin)) * WIDTH, HEIGHT);
    SDL_RenderDrawLine(rend, 0, (-yMax / (yMin - yMax)) * HEIGHT, WIDTH, (-yMax / (yMin - yMax)) * HEIGHT);

    // Draw ticks
    SDL_SetRenderDrawColor(rend, 128, 128, 128, 255);
    for (int i = 0; i < xMax; i++)
    {
        SDL_RenderDrawPoint(rend, (i - xMin / (xMax - xMin)) * WIDTH, (-yMax / (yMin - yMax)) * HEIGHT);
        SDL_RenderDrawPoint(rend, (-i - xMin / (xMax - xMin)) * WIDTH, (-yMax / (yMin - yMax)) * HEIGHT);
    }

    for (int i = 0; i < yMax; i++)
    {
        SDL_RenderDrawPoint(rend, (-xMin / (xMax - xMin)) * WIDTH, (i - yMax / (yMin - yMax)) * HEIGHT);
        SDL_RenderDrawPoint(rend, (-xMin / (xMax - xMin)) * WIDTH, (-i - yMax / (yMin - yMax)) * HEIGHT);
    }

    return;
}

//////////////////////////////

DotGraph::DotGraph() : Graph() {}
DotGraph::~DotGraph() {}

void DotGraph::refresh()
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    for (int i = 0; i < equations.size(); i++)
    {
        Pixel color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            // Transpose point for rendering
            realX = ((x - xMin) / (xMax - xMin)) * WIDTH;
            realY = ((y - yMax) / (yMin - yMax)) * HEIGHT;

            // Set color and plot point
            SDL_RenderDrawPoint(rend, realX, realY);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation modifies x.");
        }

        // cout << '\r' << "Steps: " << steps << "      " << flush;
    }

    SDL_RenderPresent(rend);

    return;
}

//////////////////////////////

struct Point
{
    Point(double X, double Y) : x(X), y(Y) {}
    Point(const Point &other) : x(other.x), y(other.y) {}
    double x, y;
};

LineGraph::LineGraph() : Graph() {}
LineGraph::~LineGraph() {}

void LineGraph::refresh()
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    vector<vector<Point>> points;

    // Prepare data
    for (int i = 0; i < equations.size(); i++)
    {
        vector<Point> eqData;

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            // Transpose point for rendering
            realX = ((x - xMin) / (xMax - xMin)) * WIDTH;
            realY = ((y - yMax) / (yMin - yMax)) * HEIGHT;

            // Log point
            eqData.push_back(Point(realX, realY));

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation modifies x.");
        }

        points.push_back(eqData);
    }

    // Graph data
    for (int i = 0; i < points.size(); i++)
    {
        Pixel color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (int j = 0; j + 1 < points[i].size(); j++)
        {
            Point a = points[i][j], b = points[i][j + 1];

            SDL_RenderDrawLine(rend, a.x, a.y, b.x, b.y);
        }
    }

    SDL_RenderPresent(rend);

    return;
}

//////////////////////////////
