#ifndef TEXT_J
#define TEXT_J

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
using namespace std;

// -lSDL_ttf

class Writer
{
public:
    Writer(SDL_Renderer *Rend, const char *Path, const int Points);
    ~Writer();

    void write(const string what, const double x, const double y, SDL_Color color);

    map<string, SDL_Texture *> surfaces;

protected:
    SDL_Renderer *rend;
    TTF_Font *font;
};

#endif
