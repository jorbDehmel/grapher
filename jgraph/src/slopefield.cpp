#include "../slopefield.hpp"
using namespace jgraph;

//////////////////////////////

void SlopeField::graphAt(const double &x, const double &y, const int &i)
{
    double realX, realY, realX2, realY2;
    double dy = (equations[i])(x, y);

    double m = sqrt(1 + pow(dy, 2));
    convertPoint(x, y, realX, realY);

    if ((dy * .5 / m) > 2)
        convertPoint(x / (dy * .5 / m), y + 1, realX2, realY2);
    else
        convertPoint(x + (.5 / m), y + (dy * .5 / m), realX2, realY2);

    drawLine(rend, realX, realY, realX2, realY2);

    return;
}

void SlopeField::refresh(bool present)
{
    this->Graph::refresh();

    for (int i = 0; i < equations.size(); i++)
    {
        SDL_Color color = COLORS[i % (COLORS.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (double x = 0; x > XMIN; x -= jgraph::TICK_SPACING_X)
        {
            for (double y = 0; y > YMIN; y -= jgraph::TICK_SPACING_Y)
                graphAt(x, y, i);
            for (double y = 0; y < YMAX; y += jgraph::TICK_SPACING_Y)
                graphAt(x, y, i);
        }

        for (double x = 0; x < XMAX; x += jgraph::TICK_SPACING_X)
        {
            for (double y = 0; y > YMIN; y -= jgraph::TICK_SPACING_Y)
                graphAt(x, y, i);
            for (double y = 0; y < YMAX; y += jgraph::TICK_SPACING_Y)
                graphAt(x, y, i);
        }
    }

    if (present)
        SDL_RenderPresent(rend);

    return;
}

void SlopeField::csv(const char *where) const
{
    ofstream out(where);
    if (!out.is_open())
        throw runtime_error("Could not open CSV file");

    for (int i = 0; i < equations.size(); i++)
    {
        string xLine, yLine, dyLine;
        xLine += "x" + to_string(i) + ", ";
        yLine += "y" + to_string(i) + ", ";
        dyLine += "dy" + to_string(i) + ", ";

        for (double x = XMIN; x < XMAX; x++)
        {
            for (double y = YMIN; y < YMAX; y++)
            {
                xLine += to_string(x) + ", ";
                yLine += to_string(y) + ", ";
                dyLine += to_string((equations[i])(x, y)) + ", ";
            }
        }

        out << xLine << '\n'
            << yLine << '\n'
            << dyLine << '\n';
    }

    out.close();
    return;
}

//////////////////////////////
