#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#ifndef noconsts
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
#endif
extern SDL_Surface *screen;
extern SDL_Surface *message;
extern SDL_Rect background;
extern TTF_Font *font;
extern SDL_Event event;
extern SDL_Color bgColor;
extern SDL_Color textColor;
extern Mix_Chunk* hit;

namespace graphics{
void apply_surface(int,int,SDL_Surface*,SDL_Surface*);
}


class Racket{
private:
    SDL_Rect shape;
    int irany;
public:
    Racket(bool);
    void moveLeft(){
        irany = -1;
    }
    void moveRight(){
        irany = 1;
    }
    void stop(){
        irany = 0;
    }
    void setAI(SDL_Rect& b);
    void move();
    float hit(const SDL_Rect& b){
        return ((b.x+b.w>shape.x) && (b.x<shape.x+shape.w))?2*(shape.x+(float)shape.w/2-b.x-b.w/2)/shape.w:-1;
    }
    void draw();
};

class Ball{
public:
    SDL_Rect shape;
    float x,y;
    float vx,vy;
    bool up;
public:
    Ball(bool);
    void move();
    int check();
    void draw();
};

#endif // GAME_H_INCLUDED
