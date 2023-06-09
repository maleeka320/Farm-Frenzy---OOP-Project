
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>
#include<SDL_ttf.h>



class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;
    //SDL_Texture* assets_for_egg=NULL;
    Mix_Music *gMusic = NULL;
    int screen;


    


public:

    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();

    void show_time(int);
    void show_money(int);
    void show_products(int);

    //all the screens
    bool startscreen();
    bool infoscreen();
    bool levelscreen();
    bool easyscreen();
    bool easyinfo();
    bool mediumscreen();
    bool mediuminfo();
    bool hardscreen();
    bool hardinfo();
    bool winningscreen();
    bool losingscreen();
};

