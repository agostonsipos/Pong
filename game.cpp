#include "game.h"
#include <cmath>
#include <iostream>

const int speed = 10*sqrt(2);

extern Racket player,computer;

Racket::Racket(bool upper):irany(0){
    shape.w = 60;
    shape.h = 10;
    shape.x = (SCREEN_WIDTH-shape.w)/2;
    shape.y = upper?0:(SCREEN_HEIGHT-shape.h);
}

void Racket::setAI(SDL_Rect& b){
	if(b.x<shape.x) moveLeft();
	else if(b.x+b.w>shape.x+shape.w) moveRight();
	else stop();
}

void Racket::move(){
	switch(irany){
		case -1: if(shape.x>=2) shape.x -= 2; break;
		case 1: if(shape.x<=SCREEN_WIDTH-shape.w-2) shape.x += 2; break;
		default: break;
	}
}

void Racket::draw(){
    SDL_FillRect(screen,&shape,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
}

Ball::Ball(bool i){
    up = i;
    vx = 5;
    vy = i?-5:5;
    shape.h = 10;
    shape.w = 10;
    x = shape.x = 0;
    y = shape.y = (SCREEN_HEIGHT-shape.h)/2;
}

void Ball::move(){
    shape.x = x += vx/4;
    shape.y = y += vy/4;
}

int Ball::check(){
    if(y>=(SCREEN_HEIGHT-20) && !up){
        float k = player.hit(shape);
        if(k!=-1){
            float deg = atan(k);
            vx = -sin(deg)*speed;
            vy = -(cos(deg)*speed);
            Mix_PlayChannel(-1,hit,0);
            up = true;
        }
        else return -1;
    }
    else if(y<=10 && up){
        float k = computer.hit(shape);
        if(k!=-1){
            float deg = atan(k);
            vx = -sin(deg)*speed;
            vy = cos(deg)*speed;
            Mix_PlayChannel(-1,hit,0);
            up = false;
        }
        else return 1;
    }
    else if(x<0)
        vx = -vx;
    else if(x>(SCREEN_WIDTH-10))
        vx = -vx;
    shape.w = 10;
    return 0;
}

void Ball::draw(){
    SDL_FillRect(screen,&shape,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
}
