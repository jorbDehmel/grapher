#include "../graph.hpp"

//////////////////////////////

namespace jgraph
{
    unsigned int HEIGHT = 256, WIDTH = 256;
    double UPSCALING_X = 1, UPSCALING_Y = 1;
    char TITLE[64] = "Jorb Grapher 0.01";

    bool SDL_IS_INITIALIZED = false;
    double LINE_W = 2;
    double TICK_SPACING_X = 1;
    double TICK_SPACING_Y = 1;

    char *FONT_PATH = "/usr/include/jgraph/fonts/pixelletters/Pixellettersfull-BnJ5.ttf";
    int FONT_POINTS = 10;

    int LABEL_LENGTH = 5;

    bool DRAW_AXIIS = true;
    bool DRAW_TICKS = true;
    bool DRAW_LABELS = true;

    int XMIN_OFFSET = 0;
    int XMAX_OFFSET = 70;
    int YMIN_OFFSET = 35;
    int YMAX_OFFSET = 0;

    SDL_Color TICK_COLOR = makeColor(192, 192, 192, 255);
    SDL_Color AXIS_COLOR = makeColor(0, 0, 0, 255);
    SDL_Color LABEL_COLOR = makeColor(0, 0, 0, 255);
}

using namespace jgraph;

//////////////////////////////

string formatDouble(const double what)
{
    string raw = to_string(what);

    if (what < 0)
        return raw.substr(0, LABEL_LENGTH + 1);
    else
        return raw.substr(0, LABEL_LENGTH);
}

//////////////////////////////

SDL_Color makeColor(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a)
{
    SDL_Color out;
    out.r = r;
    out.g = g;
    out.b = b;
    out.a = a;

    return out;
}

//////////////////////////////

void Graph::drawLine(SDL_Renderer *rend, double x1, double y1, double x2, double y2)
{
    SDL_RenderDrawLineF(rend, x1, y1, x2, y2);

    if (x1 == x2)
    {
        SDL_FRect temp;

        temp.x = x1;
        temp.y = y1;
        temp.w = LINE_W;
        temp.h = (y2 - y1);

        SDL_RenderDrawRectF(rend, &temp);
        return;
    }
    else if (y1 == y2)
    {
        SDL_FRect temp;

        temp.x = x1;
        temp.y = y1;
        temp.w = (x2 - x1);
        temp.h = LINE_W;

        SDL_RenderDrawRectF(rend, &temp);
        return;
    }
    else
    {
        if (x2 < x1)
        {
            double tempx = x1;
            x1 = x2;
            x2 = tempx;

            double tempy = y1;
            y1 = y2;
            y2 = tempy;
        }

        SDL_FRect temp;
        double dydx = (y2 - y1) / (x2 - x1);
        for (double x = x1; x < x2; x += LINE_W)
        {
            temp.x = x;
            temp.w = LINE_W;
            temp.y = y1 + (dydx * (x - x1));
            temp.h = y1 + (dydx * (LINE_W + x - x1)) - temp.y;

            if (temp.h > 0 && LINE_W > temp.h)
                temp.h = LINE_W;
            else if (temp.h < 0 && -LINE_W < temp.h)
                temp.h = -LINE_W;

            SDL_RenderDrawRectF(rend, &temp);
        }
    }

    return;
}

Graph::Graph()
{
    bgc.r = bgc.g = bgc.b = bgc.a = 255;

    xMin = yMin = -10;
    xMax = yMax = 10;

    if (!SDL_IS_INITIALIZED)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_IS_INITIALIZED = true;
    }

    wind = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    rend = SDL_CreateRenderer(wind, 0, 1);
    SDL_SetWindowSize(wind, WIDTH * UPSCALING_X, HEIGHT * UPSCALING_Y);
    SDL_RenderSetScale(rend, UPSCALING_X, UPSCALING_Y);

    writer = new Writer(rend, FONT_PATH, FONT_POINTS);

    return;
}

Graph::~Graph()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);

    SDL_Quit();

    delete writer;

    SDL_IS_INITIALIZED = false;

    return;
}

void Graph::convertPoint(const double &xIn, const double &yIn, double &xOut, double &yOut)
{
    xOut = ((xIn - xMin) / (xMax - xMin)) * WIDTH;
    yOut = ((yIn - yMax) / (yMin - yMax)) * HEIGHT;

    return;
}

void Graph::refresh()
{
    SDL_SetRenderDrawColor(rend, bgc.r, bgc.g, bgc.b, bgc.a);
    SDL_RenderClear(rend);

    // Draw ticks
    if (DRAW_TICKS)
    {
        SDL_SetRenderDrawColor(rend, TICK_COLOR.r, TICK_COLOR.g, TICK_COLOR.b, TICK_COLOR.a);
        for (int x = 0; x < xMax; x += TICK_SPACING_X)
        {
            drawLine(rend, ((x - xMin) / (xMax - xMin)) * WIDTH, 0, ((x - xMin) / (xMax - xMin)) * WIDTH, HEIGHT);
        }
        for (int x = 0; x > xMin; x -= TICK_SPACING_X)
        {
            drawLine(rend, ((x - xMin) / (xMax - xMin)) * WIDTH, 0, ((x - xMin) / (xMax - xMin)) * WIDTH, HEIGHT);
        }

        for (int y = 0; y < yMax; y += TICK_SPACING_Y)
        {
            drawLine(rend, 0, ((y - yMax) / (yMin - yMax)) * HEIGHT, WIDTH, ((y - yMax) / (yMin - yMax)) * HEIGHT);
        }
        for (int y = 0; y > yMin; y -= TICK_SPACING_Y)
        {
            drawLine(rend, 0, ((y - yMax) / (yMin - yMax)) * HEIGHT, WIDTH, ((y - yMax) / (yMin - yMax)) * HEIGHT);
        }
    }

    // Draw axii
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

    return;
}

void Graph::screenshot(const char *where) const
{
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, WIDTH * UPSCALING_X, HEIGHT * UPSCALING_Y, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(rend, NULL, 0, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, where);
    SDL_FreeSurface(sshot);

    return;
}

ostream &operator<<(ostream &stream, Graph &g)
{
    stream << "\"" << TITLE << "\"\n"
           << "\tRendering dimensions: w = " << WIDTH << ", h = " << HEIGHT << '\n'
           << "\tDisplay dimensions: w = " << WIDTH * UPSCALING_X << ", h = " << HEIGHT * UPSCALING_Y << '\n'
           << "\tLine width: " << LINE_W << '\n'
           << "\tx scale: " << TICK_SPACING_X << ", y scale: " << TICK_SPACING_Y << '\n'
           << "\tx range: (" << g.xMin << ", " << g.xMax << "), x range: (" << g.yMin << ", " << g.yMax << ")";

    return stream;
}

//////////////////////////////

void DotGraph::refresh(bool present)
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    SDL_FRect rect;
    for (int i = 0; i < equations.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            convertPoint(x, y, realX, realY);

            rect.x = realX - (LINE_W / 2.0);
            rect.y = realY - (LINE_W / 2.0);
            rect.w = rect.h = LINE_W;
            SDL_RenderDrawRectF(rend, &rect);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation modifies x.");
        }
    }

    if (present)
        SDL_RenderPresent(rend);

    return;
}

void DotGraph::csv(const char *where) const
{
    ofstream out(where);
    if (!out.is_open())
        throw runtime_error("Could not open CSV file");

    double x;
    double y;

    for (int i = 0; i < equations.size(); i++)
    {
        x = xMin;
        y = yMin;

        /*
        i am lord heljehe dejahn
        Frog tans are in ryt
        */

        string xLine, yLine;
        xLine += "x" + to_string(i) + ", ";
        yLine += "y" + to_string(i) + ", ";

        while ((equations[i])(x, y) && x < xMax)
        {
            xLine += to_string(x) + ", ";
            yLine += to_string(y) + ", ";
        }

        out << xLine << '\n'
            << yLine << '\n';
    }

    out.close();
    return;
}

//////////////////////////////

void LineGraph::refresh(bool present)
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    vector<vector<SDL_Point>> points;

    // Prepare data
    for (int i = 0; i < equations.size(); i++)
    {
        vector<SDL_Point> eqData;

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            convertPoint(x, y, realX, realY);

            // Log point
            SDL_Point temp;
            temp.x = realX;
            temp.y = realY;

            eqData.push_back(temp);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation is bounded.");
        }

        points.push_back(eqData);
    }

    // Graph data
    for (int i = 0; i < points.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (int j = 0; j + 1 < points[i].size(); j++)
        {
            SDL_Point a = points[i][j], b = points[i][j + 1];

            drawLine(rend, a.x, a.y, b.x, b.y);
        }
    }

    if (present)
        SDL_RenderPresent(rend);

    return;
}

void LineGraph::csv(const char *where) const
{
    ofstream out(where);
    if (!out.is_open())
        throw runtime_error("Could not open CSV file");

    double x;
    double y;

    for (int i = 0; i < equations.size(); i++)
    {
        x = xMin;
        y = yMin;

        /*
        i am lord heljehe dejahn
        Frog tans are in ryt
        */

        string xLine, yLine;
        xLine += "x" + to_string(i) + ", ";
        yLine += "y" + to_string(i) + ", ";

        while ((equations[i])(x, y) && x < xMax)
        {
            xLine += to_string(x) + ", ";
            yLine += to_string(y) + ", ";
        }

        out << xLine << '\n'
            << yLine << '\n';
    }

    out.close();
    return;
}

//////////////////////////////

void BarGraph::refresh(bool present)
{
    this->Graph::refresh();

    double realX, realY;

    int steps;
    double x;
    double y;

    vector<vector<SDL_Point>> points;

    // Prepare data
    for (int i = 0; i < equations.size(); i++)
    {
        vector<SDL_Point> eqData;

        steps = 0;
        x = xMin;
        y = yMin;

        while ((equations[i])(x, y) && x < xMax)
        {
            convertPoint(x, y, realX, realY);

            // Log point
            SDL_Point temp;
            temp.x = realX;
            temp.y = realY;

            eqData.push_back(temp);

            steps++;
            if (steps > 100000)
                throw runtime_error("Cannot graph: Ensure your equation is bounded.");
        }

        points.push_back(eqData);
    }

    // Graph data
    for (int i = 0; i < points.size(); i++)
    {
        SDL_Color color = colors[i % (colors.size() + 1)];
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

        for (int j = 0; j + 1 < points[i].size(); j++)
        {
            SDL_Point a = points[i][j], b = points[i][j + 1];

            SDL_Rect r;

            r.x = a.x;
            r.y = (-yMax / (yMin - yMax)) * HEIGHT;

            r.w = b.x - a.x;
            r.h = a.y - (-yMax / (yMin - yMax)) * HEIGHT;

            SDL_RenderFillRect(rend, &r);
        }
    }

    if (present)
        SDL_RenderPresent(rend);

    return;
}

void BarGraph::csv(const char *where) const
{
    ofstream out(where);
    if (!out.is_open())
        throw runtime_error("Could not open CSV file");

    double x;
    double y;

    for (int i = 0; i < equations.size(); i++)
    {
        x = xMin;
        y = yMin;

        /*
        i am lord heljehe dejahn
        Frog tans are in ryt
        */

        string xLine, yLine;
        xLine += "x" + to_string(i) + ", ";
        yLine += "y" + to_string(i) + ", ";

        while ((equations[i])(x, y) && x < xMax)
        {
            xLine += to_string(x) + ", ";
            yLine += to_string(y) + ", ";
        }

        out << xLine << '\n'
            << yLine << '\n';
    }

    out.close();
    return;
}

//////////////////////////////
