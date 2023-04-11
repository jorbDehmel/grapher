#!/bin/python3

'''
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
'''

# Rewritten in python because I know it better than bash

import sys

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print(
            "-I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lSDL2_ttf /usr/include/jgraph/bin/jgraph.a")
    elif sys.argv[1] == "--compile":
        print("-I/usr/include/SDL2 -D_REENTRANT")
    elif sys.argv[1] == "--link":
        print("-lSDL2 -lSDL2_ttf /usr/include/jgraph/bin/jgraph.a")
    else:
        raise Exception("Invalid command: Use --link or --compile")
