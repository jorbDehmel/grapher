#ifndef GRAD_FIELD_H
#define GRAD_FIELD_H

#include "graph.hpp"
#include <cmath>

SDL_Color __defaultGradFieldFill(const double &out);

class GradientField : public Graph
{
public:
    GradientField(double (*Equation)(const double x, const double y), SDL_Color (*ColorEq)(const double &out) = __defaultGradFieldFill) : Graph()
    {
        equation = Equation;
        colorEq = ColorEq;
    }

    // Update the graph window
    void refresh(bool present = true);

    // Equation to graph
    double (*equation)(const double x, const double y);

    // Save graph data to a csv file
    void csv(const char *where) const;

    // Takes an output value and returns the color to fill at that point
    SDL_Color (*colorEq)(const double &out);

protected:
    void graphAt(const double &x, const double &y);
};

#endif
