#ifndef GRAPH_H
#define GRAPH_H

#include <SDL2/SDL.h>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

//////////////////////////////

// Metavariables for graph control
namespace graph
{
    // The height and width of the graph
    extern unsigned int HEIGHT, WIDTH;

    // The upscaling scalars for x and y
    extern double UPSCALING_X, UPSCALING_Y;

    // The title of the graph's window
    extern char TITLE[64];

    // For internal use
    extern bool SDL_IS_INITIALIZED;

    // Line width for graphing
    extern double LINE_W;

    // How far apart to draw ticks
    extern double TICK_SPACING_X, TICK_SPACING_Y;
}

//////////////////////////////

// Create an SDL2 color from a given rgba
SDL_Color makeColor(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a);

// Draw a line using the width provided by LINE_W
void drawLine(SDL_Renderer *rend, double x1, double y1, double x2, double y2);

//////////////////////////////

// A basic window with a graph (virtual base class)
class Graph
{
public:
    Graph();
    ~Graph();

    // Update the graph window
    void refresh();

    // Background color
    SDL_Color bgc;

    // Graphing mins and maxs
    double xMin, xMax, yMin, yMax;

    // The colors to graph (if there are multiple lines)
    vector<SDL_Color> colors;

    // Save a screenshot of the graph
    void screenShot(const char *where) const;

protected:
    // Convert a point from actual coords to graphing coords
    void convertPoint(const double &, const double &, double &, double &);

    // Underlying SDL2 window
    SDL_Window *wind;

    // Underlying SDL2 renderer
    SDL_Renderer *rend;
};

// Output graph details to a ostream
ostream &operator<<(ostream &stream, Graph &g);

//////////////////////////////

// A dot graph, with each point being represented by a dot of size LINE_W
class DotGraph : public Graph
{
public:
    DotGraph() : Graph() {}

    // Update the graph window
    void refresh();

    // List of equations to graph
    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

// A line graph, with all data points being connected by a line of width LINE_W
class LineGraph : public Graph
{
public:
    LineGraph() : Graph() {}

    // Update the graph window
    void refresh();

    // List of equations to graph
    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

// A bar graph, with all data points being rectangles from the x-axis
class BarGraph : public Graph
{
public:
    BarGraph() : Graph() {}

    // Update the graph window
    void refresh();

    // List of equations to graph
    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

#endif
