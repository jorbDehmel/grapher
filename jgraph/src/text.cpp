#include "../text.hpp"
#include <iostream>
using namespace std;

Writer::Writer(SDL_Renderer *Rend, const char *Path, const int Points)
{
    rend = Rend;
    surfaces.clear();

    TTF_Init();

    font = TTF_OpenFont(Path, Points);
}

Writer::~Writer()
{
    TTF_CloseFont(font);
    TTF_Quit();

    for (auto p : surfaces)
    {
        SDL_DestroyTexture(p.second);
    }
    surfaces.clear();

    return;
}

void Writer::write(const string what, const double x, const double y, SDL_Color color)
{
    if (surfaces.count(what) == 0)
    {
        SDL_Surface *surf = TTF_RenderText_Solid(font, what.c_str(), color);
        surfaces[what] = SDL_CreateTextureFromSurface(rend, surf);
    }

    int w = 0, h = 0;
    SDL_QueryTexture(surfaces[what], NULL, NULL, &w, &h);
    
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(rend, surfaces[what], NULL, &dstRect);

    return;
}
