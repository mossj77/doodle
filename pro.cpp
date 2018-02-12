#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <sstream>

using namespace std;
SDL_Surface *message;
TTF_Font *font;
SDL_Color textColor = { 255, 255, 255 };

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool brick[7][7];
bool circle[7][7];
int level=1;
int best=34;
int num_ball=1;
int number;
double PI=3.1415;

int velocity = 5;
int number_of_balls = 1;

struct balls {
    int x_center;
    int y_center;
    int x_velocity;
    int y_velocity;
} ball[150];


struct bricks_p
{
    int x1;
    int y1;
    int x2;
    int y2;
    int health;
}brick_p[7][7];

void first_p(bool brick[7][7]){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            brick[i][j]=false;
        }
    }
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++)
            circle[i][j]=false;
    }
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
            brick_p[i][j].health=0;


}

void line1_brick(bool brick[7][7]){
    int num=rand()%6+1;
    int i,j;
    for(int n=0;n<num;n++){
        i=rand()%7;
        j=rand()%2;
        brick[i][0]=true;
        if(j==0)
        brick_p[i][0].health=level;
        else
        brick_p[i][0].health=2*level;
    }
}

void show_brick(SDL_Surface *d,bool brick[7][7]){
    
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            if(brick[i][j]==true){
                number=brick_p[i][j].health;
                stringstream num;
                num << number;
                boxRGBA(d,brick_p[i][j].x1,brick_p[i][j].y1,brick_p[i][j].x2,brick_p[i][j].y2,220,0,200,255);
                message = TTF_RenderText_Solid( font,num.str().c_str(), textColor );
                if(brick_p[i][j].health >= 10)
                apply_surface((brick_p[i][j].x1+brick_p[i][j].x2)/2-12,(brick_p[i][j].y1+brick_p[i][j].y2)/2-12,message,d);
                else
                    apply_surface((brick_p[i][j].x1+brick_p[i][j].x2)/2-6,(brick_p[i][j].y1+brick_p[i][j].y2)/2-12,message,d);
            }
        }
    }
}

bool shift_brick(SDL_Surface *d,bool brick[7][7],bool circle[7][7]){
    boxRGBA(d,0,105,390,500,0,0,0,255);
    for(int i=0;i<7;i++){
            if(brick[i][6]==true){
                return true;
            }
    }

    for(int j=5;j>=0;j--){
        for(int i=0;i<7;i++){
            if(brick[i][j]==true){
                brick[i][j]=false;
                brick[i][j+1]=true;
                brick_p[i][j+1].health=brick_p[i][j].health;
                brick_p[i][j].health=0;
            }
        }
    }
    for(int j=5;j>=0;j--){
        for(int i=0;i<7;i++){
            if(circle[i][j]==true){
                circle[i][j]=false;
                circle[i][j+1]=true;
            }
        }
    }

    return false;
}



void make_circls(bool brick[7][7],bool circle[7][7]){
    for(int i=0;i<7;i++){
        if(brick[i][0]==false){
            int rand1;
            rand1=rand()%2;
            if(rand1==1){
                circle[i][0]=true;
                break;
            }
        }
    }
}

void show_circle(SDL_Surface *d,bool circle[7][7]){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            if(circle[i][j]==true)
            filledCircleRGBA(d,(brick_p[i][j].x1+brick_p[i][j].x2)/2, (brick_p[i][j].y1+brick_p[i][j].y2)/2, 7, 40, 255, 40, 255);
        }
    }


}
void brick_helth(bool brick[7][7]){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            int rand1=rand()%2;
            if(brick[i][j]==true){
                if(rand1==1)
                    brick_p[i][j].health=level;
                else
                    brick_p[i][j].health=2*level;
            }
        }
    }
}

void create_ball(SDL_Surface *destination,int x_lball,int y_lball,double teta) {
    for (int k=1; k <= num_ball; k++) {
        ball[k - 1].x_center = x_lball;
        ball[k - 1].y_center = y_lball;
        ball[k - 1].x_velocity = 7*cos(teta);
        ball[k - 1].y_velocity = 7*sin(teta);
        filledCircleRGBA(destination, ball[k - 1].x_center, ball[k - 1].y_center, 5, 255, 255, 255, 255);
    }
        SDL_Delay(20);

}

void move_balls(SDL_Surface *destination,int t=1) {
    // for (int t = 1; t <= num_ball; t++) {
        if (ball[t - 1].x_center >= 385 || ball[t - 1].x_center <= 5) {
            ball[t - 1].x_velocity *= -1;
        }
        if (ball[t - 1].y_center <= 60) {
            ball[t - 1].y_velocity *= -1;
        }
        if(ball[t - 1].y_center > 540){
            return;
        }
    
        ball[t - 1].x_center += ball[t - 1].x_velocity;
        ball[t - 1].y_center -= ball[t - 1].y_velocity;
        filledCircleRGBA(destination, ball[t - 1].x_center, ball[t - 1].y_center, 5, 255, 255, 255, 255);
        // }
}
void shot_balls(SDL_Surface *d,int i){
    for(int j=1;j<=(num_ball-(i/5));j++){
        move_balls(d,j);
        SDL_Flip(d);
    }
}

void reflex_ball(){
    for(int n=0;n<num_ball;n++){
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 7; j++) {
                if(brick[i][j]==true){
                    if (ball[n].y_center + 5 >= brick_p[i][j].y1 && ball[n].y_center - 5 <= brick_p[i][j].y2 && ball[n].x_center +5 > brick_p[i][j].x1 && ball[n].x_center-5 < brick_p[i][j].x2) {
                        ball[n].y_velocity *=-1;
                        brick_p[i][j].health--;
                        break;
                    }
                    
                    if(ball[n].x_center +5 >= brick_p[i][j].x1 && ball[n].x_center -5 <= brick_p[i][j].x2 && ball[n].y_center -5 <= brick_p[i][j].y2 && ball[n].y_center +5 >= brick_p[i][j].y1){
                        ball[n].x_velocity *=-1;
                        brick_p[i][j].health--;
                    }
                    
                }
            }
        }
        
        // for(int i = 0; i < 7; i++) {
        //     for(int j = 0; j < 7; j++) {
        //         if(circle[i][j]==true){
                    
        //             if(ball[n].x_center+5 >= (brick_p[i][j].x1+brick_p[i][j].x2)/2-7 && ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].y_center-5 >=  (brick_p[i][j].y1+brick_p[i][j].y2)/2+7){
        //                 circle[i][j]=false;
        //                 num_ball++;
                        
        //             }
        //             if(ball[n].x_center-5 <= (brick_p[i][j].x1+brick_p[i][j].x2)/2+7 && ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].y_center-5 >=  (brick_p[i][j].y1+brick_p[i][j].y2)/2+7){
        //                 circle[i][j]=false;
        //                 num_ball++;
        //             }
        //             if(ball[n].y_center-5 >= (brick_p[i][j].y1+brick_p[i][j].y2)/2+7 && ball[n].x_center+5 >= (brick_p[i][j].x1+brick_p[i][j].x2)/2-7 && ball[n].x_center-5 <=  (brick_p[i][j].x1+brick_p[i][j].x2)/2+7){
        //                 circle[i][j]=false;
        //                 num_ball++;
        //             }
        //             if(ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].x_center+5 >= (brick_p[i][j].x1+brick_p[i][j].x2)/2-7 && ball[n].x_center-5 <=  (brick_p[i][j].x1+brick_p[i][j].x2)/2+7){
        //                 circle[i][j]=false;
        //                 num_ball++;
        //             }
                
        //         }
        //     }
        // }

    }
}

void check_hit(){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            if(brick_p[i][j].health<=0){
                brick[i][j]=false;
            }
        }
    }
}

int check_pts(){
    int k=0;
    for(int n=0;n<num_ball;n++){
        for(int i = 0; i < 7; i++) {
                for(int j = 0; j < 7; j++) {
                    if(circle[i][j]==true){
                        
                        if(ball[n].x_center-5 <= (brick_p[i][j].x1+brick_p[i][j].x2)/2+7 && ball[n].x_center+5 >= (brick_p[i][j].x1+brick_p[i][j].x2)/2-7 && ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].y_center-5 >=  (brick_p[i][j].y1+brick_p[i][j].y2)/2+7){
                            circle[i][j]=false;
                            k++;

                        }
                        // if(ball[n].x_center-5 <= (brick_p[i][j].x1+brick_p[i][j].x2)/2+7 && ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].y_center-5 >=  (brick_p[i][j].y1+brick_p[i][j].y2)/2+7){
                        //     circle[i][j]=false;
                        //     k++;
                        //     cout<<2;
                        // }
                        if(ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].y_center-5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2+7 && ball[n].x_center+5 >= (brick_p[i][j].x1+brick_p[i][j].x2)/2-7 && ball[n].x_center-5 <=  (brick_p[i][j].x1+brick_p[i][j].x2)/2+7){
                            circle[i][j]=false;
                            k++;
    
                        }
                        // if(ball[n].y_center+5 <= (brick_p[i][j].y1+brick_p[i][j].y2)/2-7 && ball[n].x_center+5 >= (brick_p[i][j].x1+brick_p[i][j].x2)/2-7 && ball[n].x_center-5 <=  (brick_p[i][j].x1+brick_p[i][j].x2)/2+7){
                        //     circle[i][j]=false;
                        //     k++;
                        //     cout<<4;
                        // }
                    
                    }
                }
            }
    }
    return k;
}
 

int main(){
    srand(time(0));
    
    first_p(brick);
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(390, 600, 32, 0);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    font = TTF_OpenFont( "ARLRDBD.ttf", 20);
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            brick_p[i][j].x1=5+(55*i);
            brick_p[i][j].y1=110+(55*j);
            brick_p[i][j].x2=brick_p[i][j].x1+50;
            brick_p[i][j].y2=brick_p[i][j].y1+50;
        }
    }
    SDL_Event event;
    boxRGBA(screen, 0, 55, 390, 600, 0, 0, 0, 255);
    boxRGBA(screen, 0, 0, 390, 55, 50, 50, 50, 255);
    boxRGBA(screen, 0, 545, 390, 600, 50, 50, 50, 255);
    int s=0;
    int x_lball=195,y_lball=540;
    bool flag=1;
    int speed=5;
    int alpha=90;
    double teta;
    TTF_Font *font1;
    SDL_Color textColor2 = { 50, 50, 200 };
                        boxRGBA(screen, 0, 0, 390, 600, 255, 255, 255, 255);
                        font1 = TTF_OpenFont( "ARLRDBD.ttf", 50);
                        message = TTF_RenderText_Solid( font1,"Start Game", textColor2 );
                        apply_surface(60,300,message,screen);
                        SDL_Flip(screen);
                        SDL_Delay(5000);
        while(true){
            Mix_Music *music;
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            return false;    
        }
        music = Mix_LoadMUS( "beat.wav" );
        Mix_PlayMusic( music, -1 );
            bool right=0,left=0;
            int num_circle=0;
            
            if(flag==1){
                if(s!=0){
                    if(shift_brick(screen,brick,circle)){
                        
                        boxRGBA(screen, 0, 0, 390, 600, 0, 0, 0, 255);
                        font1 = TTF_OpenFont( "ARLRDBD.ttf", 50);
                        message = TTF_RenderText_Solid( font1,"Game Over", textColor );
                        apply_surface(60,300,message,screen);
                        SDL_Flip(screen);
                        SDL_Delay(5000);
                        return 0;
                    }
                }
                line1_brick(brick);
                make_circls(brick,circle);
            }
            boxRGBA(screen, 0, 55, 390, 600, 0, 0, 0, 255);
            boxRGBA(screen, 0, 0, 390, 55, 50, 50, 50, 255);
            boxRGBA(screen, 0, 545, 390, 600, 50, 50, 50, 255);
            show_brick(screen,brick);
            show_circle(screen,circle);
                    number=level;
                    stringstream num;
                    num << number;
                    message = TTF_RenderText_Solid( font,num.str().c_str(), textColor );
                    apply_surface(80,10,message,screen);
                    message = TTF_RenderText_Solid( font,"level :", textColor );
                    apply_surface(20,10,message,screen);
                    message = TTF_RenderText_Solid( font,"best :", textColor );
                    apply_surface(250,10,message,screen);
                    stringstream num1;
                    number=best;
                    num1 << number;
                    message = TTF_RenderText_Solid( font,num1.str().c_str(), textColor );
                    apply_surface(307,10,message,screen);
            flag=0;
            
            int i=5*num_ball+4;
            s++;

            create_ball(screen,x_lball,y_lball,teta);
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_KEYDOWN){
                    switch (event.key.keysym.sym){
                        case SDLK_SPACE : {
                            flag = 1;
                            break;
                        }
                        case SDLK_RIGHT :right=1;break;
                        case SDLK_LEFT :left=1;
                    }
                }
                if (event.type == SDL_QUIT) {
                    SDL_FreeSurface(screen);
                        return 0;
                }
            }
            if(!flag){
                if(right && alpha>speed+15)
                    alpha-=speed;
                if(left && alpha<165-speed)
                    alpha+=speed;
                teta=alpha*PI/180;
                if(alpha>90){
                double x1=ball[0].x_center;
                double y1=540;
                double x2=x1+200*cos(teta-10*PI/180);
                if(x2<0)
                    x2=0;
                else if(x2>390)
                    x2=390;
                double y2=600-200*sin(teta-10*PI/180);
                lineRGBA(screen,x1,y1,x2,y2,250,35,0,255);
                }
                else{
                    double x1=ball[0].x_center;
                double y1=540;
                double x2=x1+200*cos(teta+10*PI/180);
                if(x2<0)
                    x2=0;
                else if(x2>390)
                    x2=390;
                double y2=600-200*sin(teta+10*PI/180);
                lineRGBA(screen,x1,y1,x2,y2,250,35,0,255);
                }
                SDL_Flip(screen);
            }
            if(flag==1){
                while(true){

                    boxRGBA(screen, 0, 55, 390, 600, 0, 0, 0, 255);
                    boxRGBA(screen, 0, 0, 390, 55, 50, 50, 50, 255);
                    boxRGBA(screen, 0, 545, 390, 600, 50, 50, 50, 255);
                    number=level;
                    stringstream num;
                    num << number;
                    message = TTF_RenderText_Solid( font,num.str().c_str(), textColor );
                    apply_surface(80,10,message,screen);
                    message = TTF_RenderText_Solid( font,"level :", textColor );
                    apply_surface(20,10,message,screen);

                    show_brick(screen,brick);
                    show_circle(screen,circle);
                    reflex_ball();
                    check_hit();
                    SDL_Flip(screen);
                    shot_balls(screen,i);
                    SDL_Flip(screen);
                    num_circle+=check_pts();
                    SDL_Delay(20);
                
                    if(i>0)
                    i--;
                    if(ball[num_ball-1].y_center>540){
                        x_lball=ball[0].x_center;
                        if(ball[0].x_center<=5)
                            x_lball=5;
                        if(ball[0].x_center>=185)
                            x_lball=185;
                        break;
                    }
                    while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        SDL_FreeSurface(screen);
                        return 0;
                        }   
                    }
                    // number=level;
                    // stringstream num;
                    // num << number;
                    // message = TTF_RenderText_Solid( font,num.str().c_str(), textColor );
                    // apply_surface(5,5,message,screen);
                
                    SDL_Flip(screen);
                }
            level++;  
            }
            num_ball+=num_circle;
            
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    SDL_FreeSurface(screen);
                        return 0;
                }
            }
        }

        
         while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_FreeSurface(screen);
                return 0;
            }
        }
    }