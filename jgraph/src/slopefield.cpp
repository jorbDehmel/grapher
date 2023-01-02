#include "../slopefield.hpp"

//////////////////////////////

void SlopeField::refresh()
{
    this->Graph::refresh();

    double realX, realY;
    double realX2, realY2;

    double dy;

    for (int i = 0; i < equations.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (double x = xMin; x < xMax; x++)
        {
            for (double y = yMin; y < yMax; y++)
            {
                dy = (equations[i])(x, y);

                convertPoint(x, y, realX, realY);
                convertPoint(x + .5, y + (dy * .5), realX2, realY2);

                drawLine(rend, realX, realY, realX2, realY2);
            }
        }
    }

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

        for (double x = xMin; x < xMax; x++)
        {
            for (double y = yMin; y < yMax; y++)
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
