#include "game.hpp"
#include "farm.hpp"
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <ctime>
#include<string>
#include<SDL_ttf.h>

using namespace std;
using namespace std::chrono;


// static int screen;
void Game::show_time(int t){
	TTF_Init(); //Initializes SDL_TTF for displaying text in 
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); //Opens a font style that can be downloaded as a .ttf file and sets a font size
    SDL_Color color = {1, 1, 1}; //This is the texts color that can be changed using RGB values from 0 to 255.
    string tmp = to_string(t); //converts score to string that can later be displayed using the font file - hence why we needed font.
    SDL_Surface *surfacemessage = TTF_RenderText_Solid(font, tmp.c_str(), color); //A surface is created using functions from SDL library that displays the score on the screen.
    SDL_Texture *Message = SDL_CreateTextureFromSurface(gRenderer, surfacemessage); //Converts into texture that can be displayed
    SDL_Rect Message_rect = {860, 532, 90, 30}; //create a rect for it
    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfacemessage);}


void Game::show_money(int t){
	TTF_Init(); //Initializes SDL_TTF for displaying text in 
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); //Opens a font style that can be downloaded as a .ttf file and sets a font size
    SDL_Color color = {1, 1, 1}; //This is the texts color that can be changed using RGB values from 0 to 255.
    string tmp = to_string(t); //converts score to string that can later be displayed using the font file - hence why we needed font.
    SDL_Surface *surfacemessage = TTF_RenderText_Solid(font, tmp.c_str(), color); //A surface is created using functions from SDL library that displays the score on the screen.
    SDL_Texture *Message = SDL_CreateTextureFromSurface(gRenderer, surfacemessage); //Converts into texture that can be displayed
    SDL_Rect Message_rect = {26, 555, 60, 30}; //create a rect for it
    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfacemessage);}


void Game::show_products(int t){
	TTF_Init(); //Initializes SDL_TTF for displaying text in 
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); //Opens a font style that can be downloaded as a .ttf file and sets a font size
    SDL_Color color = {1, 1, 1}; //This is the texts color that can be changed using RGB values from 0 to 255.
    string tmp = to_string(t); //converts score to string that can later be displayed using the font file - hence why we needed font.
    SDL_Surface *surfacemessage = TTF_RenderText_Solid(font, tmp.c_str(), color); //A surface is created using functions from SDL library that displays the score on the screen.
    SDL_Texture *Message = SDL_CreateTextureFromSurface(gRenderer, surfacemessage); //Converts into texture that can be displayed
    SDL_Rect Message_rect = {887, 54, 34, 24}; //create a rect for it
    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfacemessage);}



bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Farm Frenzy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}


bool Game::loadMedia() //loads all the media
{
	//Loading success flag
	bool success = true;
	screen = 1;
	assets = loadTexture("assets.png");
	//assets_for_egg =loadTexture("egg.png");
    gTexture = loadTexture("startscreen.png");
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	gMusic = Mix_LoadMUS("bgm.mp3");
	if (gMusic == NULL)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}


bool Game::startscreen() //start screen of the game
{
	//Loading success flag
	bool success = true;
	screen = 1;
    gTexture = loadTexture("startscreen.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::infoscreen() //information screen of game
{
	//Loading success flag
	bool success = true;
	screen = 2;
    gTexture = loadTexture("infoscreen.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::levelscreen() // levels screen of game 
{
	//Loading success flag
	bool success = true;
	screen = 3;
    gTexture = loadTexture("levelscreen.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::easyinfo() //instructions  for easy level
{
	//Loading success flag
	bool success = true;
	screen = 4;
    gTexture = loadTexture("easyinfo.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::easyscreen() //easy level start
{
	//Loading success flag
	bool success = true;
	screen = 5;
    gTexture = loadTexture("start.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::mediuminfo()  // instructions for medium level
{
	//Loading success flag
	bool success = true;
	screen = 6;
    gTexture = loadTexture("mediuminfo.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::mediumscreen() // medium level start
{
	//Loading success flag
	bool success = true;
	screen = 7;
    gTexture = loadTexture("start.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::hardinfo() // instructions for hard level
{
	//Loading success flag
	bool success = true;
	screen = 8;
    gTexture = loadTexture("hardinfo.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::hardscreen() //hard level start
{
	//Loading success flag
	bool success = true;
	screen = 9;
    gTexture = loadTexture("start.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::winningscreen() // when the player wins the game
{
	//Loading success flag
	bool success = true;
	screen = 10;
    gTexture = loadTexture("winningScreen.jpeg");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


bool Game::losingscreen() // when the player loses the game
{
	//Loading success flag
	bool success = true;
	screen = 11;
    gTexture = loadTexture("gameover.png");
	if(gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}


void Game::close() //closing game
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}


void Game::run( ) // main game running
{
	bool quit = false;;
	SDL_Event e;

	farmfrenzy *ff = new farmfrenzy(gRenderer, assets, 100, 100); //poiinter  of farmfrenzy
	auto start = high_resolution_clock::now(); // for clock
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			if(e.type == SDL_MOUSEBUTTONDOWN){ // below are all the conditions for switching screen 

				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse,&yMouse);
				if((xMouse>=298 && xMouse<=700) && (yMouse>=396 && yMouse<=490) && (screen==1)){
					levelscreen();
				}

				else if((xMouse>=15 && xMouse<=80) && (yMouse>=30 && yMouse<=91) && (screen==1)){
					infoscreen();
				}

				else if((xMouse>=21 && xMouse<=122) && (yMouse>=15 && yMouse<=117) && (screen==2)){
					startscreen();
				}

				else if((xMouse>=285 && xMouse<=686) && (yMouse>=146 && yMouse<=240) && (screen==3)){
					easyinfo();
				}

				else if((xMouse>=50 && xMouse<=1000) && (yMouse>=10 && yMouse<=600) && (screen==4)){
					easyscreen();
				}

				else if((xMouse>=285 && xMouse<=686) && (yMouse>=273 && yMouse<=367) && (screen==3)){
					mediuminfo();
				}

				else if((xMouse>=50 && xMouse<=1000) && (yMouse>=10 && yMouse<=600) && (screen==6)){
					mediumscreen();
				}

				else if((xMouse>=285 && xMouse<=686) && (yMouse>=394 && yMouse<=489) && (screen==3)){
					hardinfo();
				}

				else if((xMouse>=50 && xMouse<=1000) && (yMouse>=10 && yMouse<=600) && (screen==8)){
					hardscreen();
				}

				else if((xMouse>=50 && xMouse<=1000) && (yMouse>=10 && yMouse<=600) && (screen==10)){
					ff->countProduct = 0;
					levelscreen();
				}

				else if((xMouse>=50 && xMouse<=1000) && (yMouse>=10 && yMouse<=600) && (screen==11)){
					ff->countProduct = 0;
					levelscreen();
				}
			}

			if (Mix_PlayingMusic() == 0) //condition for music 
			{
				Mix_PlayMusic(gMusic, 2);
			}
		}


		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer



		//***********************draw the objects here********************



// If conditions for all the different levels below

		if(screen==5){ // Easy Level
			
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if(ff->money>=100){
					ff->createChicken(x, y);
					cout<<"current money is "<<ff->currentMoney()<<endl;}
				if(ff->money>=200){
					ff->createPig(x, y);
					cout<<"current money is "<<ff->currentMoney()<<endl;
				}
				std::cout << "Mouse clicked at: " << x << " -- " << y << std::endl;
				ff->removeProduct(x, y);
				cout<<"current money is "<<ff->currentMoney()<<endl;
			}

			ff->drawObjects();
			ff->drawProducts();

			
			if(ff->collectedProducts()==6){ //player has collected 6 products
				screen=10;
				winningscreen();
			}

			int money=ff->currentMoney();
			int products=ff->collectedProducts();
			show_money(money);
			show_products(products);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			int t = 195 - duration.count(); //time allocated per level
			show_time(t);

			if (t<=0){ //losing condition
				screen = 11;
				losingscreen();
			}

		}


		

		if(screen == 7) { // Medium Level

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse,&yMouse);
				if(ff->money>=100){
					ff->createChicken(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;}
				if(ff->money>=200){
					ff->createPig(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;
				}
				if(ff->money>=150){
					ff->createSheep(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;
				}
				std::cout << "Mouse clicked at: " << xMouse << " -- " << yMouse << std::endl;
				ff->removeProduct(xMouse, yMouse);
			}

			ff->drawObjects();
			ff->drawProducts();

			if(ff->collectedProducts()==8){ //player has collected 8 products
				screen=10;
				winningscreen();
			}

			int money=ff->currentMoney();
			int products=ff->collectedProducts();
			show_money(money);
			show_products(products);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			int t = 125 - duration.count(); //time allocated per level
			show_time(t);

			if (t<=0){ //losing condition
				screen = 11;
				losingscreen();
			}
		}





		if(screen == 9) { // Hard Level
			
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse,&yMouse);
				if(ff->money>=100){
					ff->createChicken(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;}
				if(ff->money>=200){
					ff->createPig(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;
				}
				if(ff->money>=300){
					ff->createCow(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;
				}
				if(ff->money>=150){
					ff->createSheep(xMouse, yMouse);
					cout<<"current money is "<<ff->currentMoney()<<endl;
				}

				std::cout << "Mouse clicked at: " << xMouse << " -- " << yMouse << std::endl;
				ff->removeProduct(xMouse, yMouse);
			}

			ff->drawObjects();
			ff->drawProducts();

			if(ff->collectedProducts()==10){ //player has collected 10 products
				screen=10;
				winningscreen();
			}

			int money=ff->currentMoney();
			int products=ff->collectedProducts();
			show_money(money);
			show_products(products);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			int t = 95 - duration.count(); //time allocated per level
			show_time(t);

			if (t<=0){ //losing condition
				screen = 11;
				losingscreen();
			}
		}


		//****************************************************************
    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(100);	//causes sdl engine to delay for specified miliseconds
	}

	ff->~farmfrenzy();
	delete ff;	
	ff = nullptr;
}
