#include "../gradientfield.hpp"
using namespace jgraph;

// Sigmoid function times 255
// -infinity -> black
// infinity -> white
SDL_Color __defaultGradFieldFill(const double &in)
{
    Uint8 val = 255 / (1 + pow(2.718281821, -(in / 50)));

    SDL_Color out;
    out.a = 255;
    out.r = out.g = out.b = val;

    return out;
}

// Update the graph window
void GradientField::refresh(bool present)
{
    for (double x = 0; x >= xMin; x -= TICK_SPACING_X)
    {
        for (double y = 0; y >= yMin; y -= TICK_SPACING_Y)
            graphAt(x, y);
        for (double y = 0; y <= yMax; y += TICK_SPACING_Y)
            graphAt(x, y);
    }

    for (double x = 0; x <= xMax; x += TICK_SPACING_X)
    {
        for (double y = 0; y >= yMin; y -= TICK_SPACING_Y)
            graphAt(x, y);
        for (double y = 0; y <= yMax; y += TICK_SPACING_Y)
            graphAt(x, y);
    }

    if (DRAW_AXIIS)
    {
        SDL_SetRenderDrawColor(rend, AXIS_COLOR.r, AXIS_COLOR.g, AXIS_COLOR.b, AXIS_COLOR.a);
        drawLine(rend, (-xMin / (xMax - xMin)) * WIDTH, 0, (-xMin / (xMax - xMin)) * WIDTH, HEIGHT);
        drawLine(rend, 0, (-yMax / (yMin - yMax)) * HEIGHT, WIDTH, (-yMax / (yMin - yMax)) * HEIGHT);
    }

    if (DRAW_LABELS)
    {
        // Write labels
        writer->write(formatDouble(xMin), XMIN_OFFSET, (-yMax / (yMin - yMax)) * HEIGHT, LABEL_COLOR);
        writer->write(formatDouble(xMax), WIDTH - XMAX_OFFSET, (-yMax / (yMin - yMax)) * HEIGHT, LABEL_COLOR);

        writer->write(formatDouble(yMin), (-xMin / (xMax - xMin)) * WIDTH, HEIGHT - YMIN_OFFSET, LABEL_COLOR);
        writer->write(formatDouble(yMax), (-xMin / (xMax - xMin)) * WIDTH, YMAX_OFFSET, LABEL_COLOR);

        writer->write("0", (-xMin / (xMax - xMin)) * WIDTH - FONT_POINTS, (-yMax / (yMin - yMax)) * HEIGHT, LABEL_COLOR);
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
    convertPoint(x - (TICK_SPACING_X / 2), y - (TICK_SPACING_Y / 2), realX, realY);
    convertPoint(x + (TICK_SPACING_X / 2), y + (TICK_SPACING_Y / 2), realX2, realY2);

    SDL_FRect toFill;
    toFill.x = realX;
    toFill.y = realY;
    toFill.w = realX2 - realX;
    toFill.h = realY2 - realY;

    SDL_RenderFillRectF(rend, &toFill);

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
