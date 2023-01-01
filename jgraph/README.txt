~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jgraph - Graphing library for C++

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Jordan "Jorb" Dehmel, 2022 - 2023
jdehmel@outlook.com
github.com/jorbDehmel/jgraph
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Installation:

    This library only supports Linux. It requires SDL2,
which will need to be required before this.

    To install this library, open this folder in
terminal and enter `make install`. From then on, you can
use the following in your C++ files:

    #include <jgraph/jgraph.hpp>

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Compiling:

    You must include /usr/include/jgraph/bin/jgraph.a as
the FINAL argument of your compilation command (this
file will be created upon running `make install`).

    This library depends of SDL2, and therefor you must
include the following in your compilation command:

    `sdl2-config --cflags --libs`

For example:

g++ `sdl2-config --cflags --libs` ex.cpp \
    /usr/include/jgraph/bin/jgraph.a 

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