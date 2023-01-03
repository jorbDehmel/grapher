#include "../gradientfield.hpp"

// Sigmoid function times 255
// -infinity -> black
// infinity -> white
SDL_Color __defaultGradFieldFill(const double &in)
{
    Uint8 val = 255 / (1 + pow(2.718281821, -in));

    SDL_Color out;
    out.a = 255;
    out.r = out.g = out.b = val;

    return out;
}

// Update the graph window
void GradientField::refresh(bool present)
{
    for (double x = 0; x > xMin; x -= jgraph::TICK_SPACING_X)
    {
        for (double y = 0; y > yMin; y -= jgraph::TICK_SPACING_Y)
            graphAt(x, y);
        for (double y = 0; y < yMax; y += jgraph::TICK_SPACING_Y)
            graphAt(x, y);
    }

    for (double x = 0; x < xMax; x += jgraph::TICK_SPACING_X)
    {
        for (double y = 0; y > yMin; y -= jgraph::TICK_SPACING_Y)
            graphAt(x, y);
        for (double y = 0; y < yMax; y += jgraph::TICK_SPACING_Y)
            graphAt(x, y);
    }

    if (present)
        SDL_RenderPresent(rend);

    return;
}

void GradientField::graphAt(const double &x, const double &y)
{
    double out = equation(x, y);

    SDL_Color c = colorEq(out);
    SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);

    double realX, realY, realX2, realY2;
    convertPoint(x, y, realX, realY);
    convertPoint(x + jgraph::TICK_SPACING_X, y + jgraph::TICK_SPACING_Y, realX2, realY2);

    SDL_FRect toFill;
    toFill.x = realX;
    toFill.y = realY;
    toFill.w = realX2 - realX;
    toFill.h = realY2 - realY;

    SDL_RenderDrawRectF(rend, &toFill);

    return;
}

void GradientField::csv(const char *where) const
{
    ofstream out(where);
    if (!out.is_open())
        throw runtime_error("Could not open CSV file");

    string xLine, yLine, dyLine;
    xLine += "x, ";
    yLine += "y, ";
    dyLine += "out, ";

    for (double x = xMin; x < xMax; x++)
    {
        for (double y = yMin; y < yMax; y++)
        {
            xLine += to_string(x) + ", ";
            yLine += to_string(y) + ", ";
            dyLine += to_string(equation(x, y)) + ", ";
        }
    }

    out << xLine << '\n'
        << yLine << '\n'
        << dyLine;

    out.close();
    return;
}
