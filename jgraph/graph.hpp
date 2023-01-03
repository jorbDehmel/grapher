#ifndef GRAPH_H
#define GRAPH_H

#include <SDL2/SDL.h>
#include "text.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//////////////////////////////

// Metavariables for graph control
namespace jgraph
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

    // Path to the .ttf font to write in
    extern char *FONT_PATH;

    // Size of the font to write in
    extern int FONT_POINTS;

    // Number of digits to write (excluding sign)
    extern int LABEL_LENGTH;

    // Whether or not to draw the x and y axiis
    extern bool DRAW_AXIIS;

    // Whether or not to draw the ticks
    extern bool DRAW_TICKS;

    // Whether or not to draw labels
    extern bool DRAW_LABELS;

    // Color to draw ticks in
    extern SDL_Color TICK_COLOR;

    // Color to draw axiis in
    extern SDL_Color AXIS_COLOR;

    // Color to draw labels in
    extern SDL_Color LABEL_COLOR;
}

//////////////////////////////

// Create an SDL2 color from a given rgba
SDL_Color makeColor(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a);

//////////////////////////////

// A basic window with a graph (virtual base class)
class Graph
{
public:
    Graph();
    ~Graph();

    // Draw a line using appropriate line width
    void drawLine(SDL_Renderer *rend, double x1, double y1, double x2, double y2);

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

    // Underlying SDL2 window
    SDL_Window *wind;

    // Underlying SDL2 renderer
    SDL_Renderer *rend;

    // Text added
    Writer *writer;

protected:
    // Convert a point from actual coords to graphing coords
    void convertPoint(const double &, const double &, double &, double &);
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
    void refresh(bool present = true);

    // Save graph data to a csv file
    void csv(const char *where) const;

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
    void refresh(bool present = true);

    // Save graph data to a csv file
    void csv(const char *where) const;

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
    void refresh(bool present = true);

    // Save graph data to a csv file
    void csv(const char *where) const;

    // List of equations to graph
    vector<bool (*)(double &, double &)> equations;
};

//////////////////////////////

#endif
