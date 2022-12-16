#ifndef GRAPH_H
#define GRAPH_H

#include <SDL2/SDL.h>
#include <vector>
#include <stdexcept>
using namespace std;

//////////////////////////////

extern unsigned int HEIGHT, WIDTH;
extern double UPSCALING_X, UPSCALING_Y;
extern char TITLE[64];

extern bool SDL_IS_INITIALIZED;

//////////////////////////////

class Pixel
{
public:
    Pixel() : r(0), g(0), b(0), a(0) {}
    Pixel(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A) {}
    unsigned char r, g, b, a;
};

//////////////////////////////

class Graph
{
public:
    Graph();
    ~Graph();
    void refresh();

    Pixel bgc;

    double xMin, xMax, yMin, yMax;
    vector<bool (*)(double &, double &)> equations;
    vector<Pixel> colors;

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
};

//////////////////////////////

class LineGraph : public Graph
{
public:
    LineGraph() : Graph() {}
    void refresh();
};

//////////////////////////////

class BarGraph : public Graph
{
public:
    BarGraph() : Graph() {}
    void refresh();
};

#endif
