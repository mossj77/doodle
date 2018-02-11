#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "SDL/SDL_mixer.h"
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
TTF_Font *font1;
SDL_Color textColor = { 25, 190, 240 };
// const int SCREEN_WIDTH = 100;
// const int SCREEN_HEIGHT = 40;
// const int SCREEN_BPP = 15;
// void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
const float FPS=50.0;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
}
void loose(int x, int y, int xenem[50], int yenem, int numenem)
{
    for(int i=0; i<numenem; i++)
        if((x+5>=xenem[i] && x-5<=xenem[i] && y+5<=yenem+15 && y+5>=yenem-10) || (x-5>=xenem[i] && x-5<=xenem[i]+8 && y-5<=yenem+15 && y-5>=yenem-10))
        {
            cout<<"You Loose !!";
            boxRGBA(screen, 0, 0, 400, 700, 0, 0, 0, 255);
            font1 = TTF_OpenFont( "ARLRDBD.ttf", 50);
            message = TTF_RenderText_Solid( font1,"Game Over", textColor );
            apply_surface(60,300,message,screen);
            SDL_Flip(screen);
            SDL_Delay(5000);
            exit(1);
        }

    if(y>=700)
    {
        cout<<"You Loose !!";
        boxRGBA(screen, 0, 0, 400, 700, 0, 0, 0, 255);
        font1 = TTF_OpenFont( "ARLRDBD.ttf", 50);
        message = TTF_RenderText_Solid( font1,"Game Over", textColor );
        apply_surface(60,300,message,screen);
        SDL_Flip(screen);
        SDL_Delay(5000);
        exit(1);
    }

}

int changex(int x)
{
    	if(!SDL_PollEvent(&event));
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_RIGHT)
				{
					x+=5;
					if(x==400)
					x=0;
				}
			if(event.key.keysym.sym == SDLK_LEFT)
				{
					x-=5;
					if(x==0)
					x=400;
				}
		}

return(x);
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

 void buildenemy(int xenem[50], int yenem, int numenem)
{
    for(int i=0; i<numenem; i++)
    roundedBoxRGBA(screen, xenem[i], yenem, xenem[i]+8, yenem+10,1,255,0,0,255);
}

 void buildtir(int xtir,int ytir)
{
    roundedBoxRGBA(screen, xtir, ytir, xtir+2, ytir+10,2,0,255,0,255);

}
 void porx(int array[11], int numx)
{
	int x;
	srand(time(0));
	for(int i=1; i<numx; i++)
    	{
            x=rand()%9+1;
            x*=40;
            array[i]=x;
        }
	array[0]=180;
}

 void pory(int array[11], int numy)
{
	int c=1;
	for(int y=700; y>0; y-=70)
    	{
        	array[c]=y;
            if(c<numy-1)
                c++;
            else
                break;
        }
	array[0]=630;

}

 void pory2(int array[11], int numy)
{
    int c=1;
	for(int y=0; y>-700; y-=70)
    	{
        	array[c]=y;
            if(c<numy)
                c++;
            else
            break;
        }
    array[0]=30;

}

 void porxenem(int array[50], int numxenem)
{
    int c=0;
	for(int x=0; x<400; x+=8)
    	{
        	array[c]=x;
            if(c<numxenem)
                c++;
            else
            break;
        }

}

 int jump(int y, int sy, int bala1paen0)
{

	if(bala1paen0==1)
	{
		if(sy<40 && sy>=0)
			y-=10;
		else if(sy<70 && sy>=40)
			y-=6;
		else if(sy<90 && sy>=70)
			y-=4;
		else if(sy<100 && sy>=90)
			y-=1;

	}
	else if(bala1paen0==0)
	{
		if(sy<=40)
			y+=10;
		else if(sy<=70 && sy>40)
			y+=6;
		else if(sy<=90 && sy>70)
			y+=4;
		else if(sy<=103 && sy>90)
			y+=1;
	}
	sy=0;

	return (y);
}

 int jumpfanar(int y, int sy, int bala1paen0)
{
	if(bala1paen0==1)
	{
		if(sy<80 && sy>=0)
			y-=20;
		else if(sy<140 && sy>=80)
			y-=12;
		else if(sy<180 && sy>=140)
			y-=8;
		else if(sy<200 && sy>=180)
			y-=2;

	}
	else if(bala1paen0==0)
	{
		if(sy<=80)
			y+=20;
		else if(sy<=140 && sy>80)
			y+=12;
		else if(sy<=180 && sy>140)
			y+=8;
		else if(sy<=200 && sy>180)
			y+=2;
	}
	sy=0;

	return (y);
}
 void  print_score(int n)
{
        string Result;
    	stringstream convert;
        convert << n;
        Result = convert.str();
        SDL_Color textColor={25, 190, 240};
        message = TTF_RenderText_Solid( font,Result.c_str(),textColor );
        apply_surface(20, 20, message, screen );
        SDL_Flip(screen);
}
 void count_score(int m)
{
    int ctr=0;
    for(int i=1;i<=m;i++)
    {
        ctr+=i;
        print_score(ctr);
    }

}

 void middle(int y, int bala1paen0, int paresh, int numy, int ypos[11], int y2pos[11], int s2y)
{
    int score1;
    int score2;
    int score;
    if(y<=350 && bala1paen0==0)
    {
        score1=s2y;
        if(paresh==1)
        {
        if(s2y<=40)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=10;
            y2pos[i]+=10;
            s2y+=10;
            }
        else if(s2y<=70 && s2y>40)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=6;
            y2pos[i]+=6;
            s2y+=6;
            }
        else if(s2y<=90 && s2y>70)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=4;
            y2pos[i]+=4;
            s2y+=4;
            }
        else if(s2y<=100 && s2y>90)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=1;
            y2pos[i]+=1;
            s2y+=1;
            }
            score2=s2y;
            score=score2-score1;
            count_score(score);
        }
        if(paresh==2)
        {
            if(s2y<=80)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=20;
            y2pos[i]+=20;
            s2y+=20;
            }
        else if(s2y<=140 && s2y>80)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=12;
            y2pos[i]+=12;
            s2y+=12;
            }
        else if(s2y<=180 && s2y>140)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=8;
            y2pos[i]+=8;
            s2y+=8;
            }
        else if(s2y<=200 && s2y>180)
            for(int i=0; i<numy; i++)
            {
            ypos[i]+=2;
            y2pos[i]+=2;
            s2y+=2;
            }
        }

    score2=s2y;
    score=score2-score1;
    count_score(score);

    }


}

 void enemy(int xenem[50], int yenem, int numenem)
{
    buildenemy(xenem, yenem, numenem);
}

 void stir(int xtir, int ytir, int xenem[50], int yenem, int numenem)
{
    for(int i=0; i<numenem; i++)
    if(xtir>=xenem[i] && xtir<=xenem[i]+8 && ytir>=yenem && ytir<=yenem+15)
    {
        xenem[i]=0;
        ytir=600;
        xtir=10;
    }
}



 void charac()
{
	static int x=200;
	static int y=600;
	static int sy=0;
	static int y1=0;
	static int xtir;
	static int ytir;
	static int tir=0;
	double divar=1;

    const int numx=11;
    const int numy=11;
    const int numyf=11;
    const int numenem=50;
    int xpos[numx];
    int ypos[numy];
    int y2pos[numy];
    double yenem=0;
    int xenem[numenem];

	int bala1paen0=1;
	int paresh=0;
    int paresh2=0;
	int s2y;

    porxenem(xenem, numenem);
	porx(xpos, numx);
	pory(ypos, numy);
	pory2(y2pos, numy);


    Timer fps;
    bool quit=false;
	for(int i=0;!quit; i++)
	{
	fps.start();

    for(int i=0; i<numy; i++)
    {
        if(i%3==0 && i!=0)
        if(x>=xpos[i]+10 && y>=ypos[i]-10 && x<=xpos[i]+30 && y<=ypos[i] && bala1paen0==0)
        {paresh=2;
        bala1paen0=1;
        sy=0;
        break;}
        if(i%3==0 && i!=0)
        if(x>=xpos[i]+10 && y>=y2pos[i]-10 && x<=xpos[i]+30 && y<=y2pos[i] && bala1paen0==0)
        {paresh=2;
        bala1paen0=1;
        sy=0;
        break;}
    }

    for(int j=0; j<numy; j++)
    {
        if(y>=ypos[j] && y<=ypos[j]+15 && x>=xpos[j] && x<=xpos[j]+40 && bala1paen0==0)
            {paresh=1;
            bala1paen0=1;
            sy=0;
            break;}
        if(y>=y2pos[j] && y<=y2pos[j]+15 && x>=xpos[j] && x<=xpos[j]+40 && bala1paen0==0)
            {paresh=1;
            bala1paen0=1;
            sy=0;
            break;}
    }

    if(ypos[0]>=690 && ypos[0]<=710)
        pory2(y2pos, numy);

    if(y2pos[0]>=690 && y2pos[0]<=710)
        pory2(ypos, numy);

    //cout<<"dfsagggdhghdah=="<<paresh<<"\n";

    //cout<<"s2y=="<<s2y<<"\n";

    if(paresh==1)
    {
		paresh2=0;
    }

    if(paresh==2)
    {
        paresh2=3;
    }


		build(xpos, ypos, y2pos, numy);
		buildfanar(xpos, ypos, y2pos, numy);

    //cout<<"b2=="<<paresh2<<"\n";
    if(paresh2==0 || paresh==1)
    {
		y1=y;
        y=jump(y,sy,bala1paen0);
		y1-=y;
		sy+=y1;
		s2y=sy;
		if(sy==100 || sy==103)
		bala1paen0=0;
        //s2y=0;
    }


    if(paresh2==3 || paresh==2)
    {
        y1=y;
        y=jumpfanar(y,sy,bala1paen0);
		y1-=y;
		sy+=y1;
		s2y=sy;
		if(sy>=200)
		bala1paen0=0;
		//s2y=0;
    }

        x=changex(x);

        enemy(xenem, yenem, numenem);
        yenem+=divar;

        if(yenem>=700 && yenem<=710)
        {
            porxenem(xenem, numenem);
            yenem=0;
            divar+=0.2;
        }

        if(!SDL_PollEvent(&event));
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_SPACE)
            {
                xtir=x;
                ytir=y;
                tir=1;
            }
        }

        if(tir==1)
        buildtir(xtir,ytir);
        ytir-=5;
        stir(xtir,ytir,xenem,yenem,numenem);
        loose(x,y,xenem,yenem,numenem);
        middle(y,bala1paen0,paresh,numy,ypos,y2pos,s2y);

        filledEllipseRGBA(screen, x , y , 10, 10, 255, 255, 255, 255);

        SDL_Flip(screen);
	    boxRGBA(screen, 0, 0, 400, 700,0,0,0,255);
	    	    //cout<<"score"<<endl;

    	if( fps.get_ticks() < 1000 / FPS )
                SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );

        if( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                SDL_Quit();
            }
        }
            lineRGBA(screen,0,320,400,320,250,35,0,255);
                SDL_Flip(screen);
            Mix_Music *music;
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            // return false;    
        }
        music = Mix_LoadMUS( "beat.wav" );
        Mix_PlayMusic( music, -1 );
            bool right=0,left=0;
            int num_circle=0;

	}
}

//  void menu()
// {
//     bool menu=true;
//     cout<<"press up"<<"\n";
//     while(menu==true)
//     {
//         filledEllipseRGBA(screen, 200 , 350 , 10, 10, 255, 255, 255, 255);

//     	if(!SDL_PollEvent(&event));
// 		if(event.type == SDL_KEYDOWN)
// 		{
// 			if(event.key.keysym.sym == SDLK_UP)
// 			menu=false;
//         }

//         SDL_Flip(screen);
//     }
// }

int main()
{
    SDL_Color textColor2 = { 0, 50, 200 };
    boxRGBA(screen, 0, 0, 400, 700, 255, 255, 255, 255);
    font1 = TTF_OpenFont( "ARLRDBD.ttf", 50);
    message = TTF_RenderText_Solid( font1,"Start Game", textColor );
    apply_surface(200,300,message,screen);
    SDL_Flip(screen);
    SDL_Delay(3000);
    TTF_Init();
    // font = TTF_OpenFont( "lazy.ttf", 28 );
    while(true)
    {
        // menu();
        charac();
    }
    return 0;
}
