~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jgraph - Graphing library for C++
Version 0.1.0

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Jordan "Jorb" Dehmel, 2022 - 2023
jdehmel@outlook.com
github.com/jorbDehmel/jgraph
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Installation:

    This library only supports Linux. It requires SDL2,
which will be installed with this library.

    To install this library, open this folder in
terminal and enter `make install`. From then on, you can
use the following in your C++ files:

    #include <jgraph/jgraph.hpp>

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Compiling:

    You must include /usr/include/jgraph/bin/jgraph.a as
the FINAL argument of your compilation command (this
file will be created upon running `make install`).

    This library depends on SDL2, and therefor you must
include the following in your compilation command:

    `sdl2-config --cflags --libs` -lSDL2_ttf

For example:

g++ `sdl2-config --cflags --libs` -lSDL2_ttf ex.cpp \
    /usr/include/jgraph/bin/jgraph.a 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Adding text:

    To initialize a Writer object for adding text, use
the following form:

Writer textWriter(WINDOW, RENDERER, "PATH.ttf", POINTS);

    Where, for a Graph g, you could use g.wind and
g.rend to retrieve the window and renderer respectively.

    To write text after this, use the form:

textWriter.write("TEXT HERE", x, y, SDL_Color COLOR);

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The refresh method:

    The refresh(bool present) method on Graph objects
updates the graph. If the "present" parameter is true,
it will present this updated graph to the screen. If it
is false, you must manually call SDL_RenderPresent(rend)
function after calling refresh. This is useful if you
want to manually edit the graph before it is presented
(IE adding extra text).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Functions and parametric equations:

    Graphable equations must be represented by functions
of the form:

    bool foobar(double &x, double &y)
    {
        x += DX;
        y = func(x);

        return continuesGraphingTrue;
    }

    The system will start at x = xMin and continue
calling the update function until it returns false or
x exceeds xMax.

    These equations can be added to a graph's list of
equations, and the graph's colors list can be modified
to graph different equations in this list in different
colors.

    You can use external variables to create parametric
functions (since both x and y can be independant with
this function form).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SlopeFields and differential equations:

    Slope field equations work the safe, but take a
slightly different form:

    double dy(const double x, const double y)
    {
        return foobar(x, y);
    }

    In this form, the return value is the change in y
over x (or t, or whatever). The parameters x and y are
both constant, and thus do not need to be incremented
for this type of equation.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GradientFields:

    Gradient fields function like slope fields, but
instead of a vector representing the value at a given
point (x, y), this value is represented by the color at
the point.

    This graph cannot only plot 1 equation, and takes an
additional function which determines the color given the
output value. The default function maps high values to
light colors and low values to dark colors.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The csv.hpp file and .csv parsing:

    This file provides basic functionality for loading
.csv files (which can be easily graphed). It can load
them via doubles (useful for graphing) or strings
(useful for other .csv uses). It can also load both
vertical and horizontal CSVs. It can handle irregular
whitespace and collumn names as well. The output of
these functions are CSV<class T> objects, which store
the names of the collumns and a 2D vector of their data
(of type T).

    Example of a vertical csv file:

name1,  name2
1,      4
16,     105
12,     -12.5

    Example of a horizontal csv file:
    
name1, 1, 16, 12
name2, 4, 105, -12.5

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Included fonts from:
https://www.fontspace.com/pixelletters-font-f22954
https://fonts.google.com/specimen/Open+Sans

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

License (via MIT)

Copyright © 2022 Jordan Dehmel

Permission is hereby granted, free of charge, to any 
person obtaining a copy of this software and associated 
documentation files (the “Software”), to deal in the 
Software without restriction, including without
limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice 
shall be included in all copies or substantial portions 
of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF 
ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN  CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~