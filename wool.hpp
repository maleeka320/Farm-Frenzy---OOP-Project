#include<SDL.h>
#include "food.hpp"

#ifndef UNIT
#define UNIT

class wool: public food{
SDL_Rect srcRect, moverRect;

public:
    void draw(SDL_Renderer*, SDL_Texture* assets); //draw function of wool
    wool(SDL_Renderer*, SDL_Texture*, int, int);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    char type();
    };
#endif