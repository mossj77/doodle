#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "time.h"
#include <string>
#include <sstream>
using namespace std;
SDL_Surface* screen = SDL_SetVideoMode(400, 700 ,32, 0);
SDL_Event event;
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
//SDL_Surface *screen1 = NULL;
TTF_Font *font = NULL;
SDL_Color textColor = { 25, 190, 240 };
// const int SCREEN_WIDTH = 100;
// const int SCREEN_HEIGHT = 40;
// const int SCREEN_BPP = 15;
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
const float FPS=50.0;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip  )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void build(int xpos[11], int ypos[11], int y2pos[11], int numy)
{
	for(int i=0; i<numy; i++)
	    {
			roundedBoxRGBA(screen, xpos[i], ypos[i], xpos[i]+40, ypos[i]+10,2,255,255,255,255);
			roundedBoxRGBA(screen, xpos[i], y2pos[i], xpos[i]+40, y2pos[i]+10,2,255,255,255,255);
		}
}

void buildfanar(int xpos[11], int ypos[11], int y2pos[11], int numy2)
{
    for(int i=0; i<numy2; i++)
            if(i%3==0 && i!=0)
            {
                boxRGBA(screen, xpos[i]+10, ypos[i]-10, xpos[i]+30, ypos[i] ,0,0,255,255);
                boxRGBA(screen, xpos[i]+10, y2pos[i]-10, xpos[i]+30, y2pos[i] ,0,0,255,255);
            }
}

int main()
{
    TTF_Init();
    font = TTF_OpenFont( "lazy.ttf", 28 );
    while(true)
    {
        // menu();
        charac();
    }
    return 0;
}