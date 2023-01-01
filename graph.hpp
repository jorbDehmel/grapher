#ifndef GRAPH_H
#define GRAPH_H

#include <SDL2/SDL.h>
#include <vector>
#include <stdexcept>
using namespace std;

//////////////////////////////

namespace graph
{
    extern unsigned int HEIGHT, WIDTH;
    extern double UPSCALING_X, UPSCALING_Y;
    extern char TITLE[64];

    extern bool SDL_IS_INITIALIZED;
}

//////////////////////////////

SDL_Color makeColor(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a);

class GraphFunction
{
public:
    GraphFunction(bool (*func)(double &, double &)) : eval(func) {}

    // bool operator()() { return eval(); }
    bool (*eval)(double &, double &);
};

//////////////////////////////

class Graph
{
public:
    Graph();
    ~Graph();
    void refresh();

    SDL_Color bgc;

    double xMin, xMax, yMin, yMax;
    vector<SDL_Color> colors;

protected:
    void convertPoint(const double &, const double &, double &, double &);

    SDL_Window *wind;
    SDL_Renderer *rend;
};

//////////////////////////////

class DotGraph : public Graph
{
public:
    DotGraph() : Graph() {}
    void refresh();

    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

class LineGraph : public Graph
{
public:
    LineGraph() : Graph() {}
    void refresh();

    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

class BarGraph : public Graph
{
public:
    BarGraph() : Graph() {}
    void refresh();

    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

#endif
