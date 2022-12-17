#ifndef SLOPEFIELD_H
#define SLOPEFIELD_H

#include "graph.hpp"

//////////////////////////////

class SlopeField : public Graph
{
public:
    SlopeField() : Graph() {}
    void refresh();

    vector<double (*)(double &x, double &y)> equations;
};

//////////////////////////////

#endif
