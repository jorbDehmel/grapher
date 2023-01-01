#ifndef SLOPEFIELD_H
#define SLOPEFIELD_H

#include "graph.hpp"

//////////////////////////////

// A slope field graph, with the slope at a point (x, y) being represented
// by a scaled down vector
class SlopeField : public Graph
{
public:
    SlopeField() : Graph() {}

    // Update the graph window
    void refresh();

    // List of equations to graph
    vector<double (*)(const double x, const double y)> equations;
};

//////////////////////////////

#endif
