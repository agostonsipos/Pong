#include "game.h"
#include "events.h"
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Rect background;
TTF_Font *font = NULL;
SDL_Event event;
SDL_Color bgColor = { 0, 0, 0 };
SDL_Color textColor = { 255, 255, 255 };
Mix_Chunk* hit = NULL;

Racket player(false), computer(true);
int a, b;

void graphics::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void drawPoints(int a, int b){
	char buf1[3], buf2[3];
	sprintf(buf1, "%d", a);
	sprintf(buf2, "%d", b);
    message = TTF_RenderText_Shaded( font, buf1, textColor , bgColor);
    graphics::apply_surface(0,SCREEN_HEIGHT-50,message,screen);
    SDL_FreeSurface(message);
    message = TTF_RenderText_Shaded( font, buf2, textColor , bgColor);
    graphics::apply_surface(0,20,message,screen);
    SDL_FreeSurface(message);
}

void gameloop(Ball& ball){
    while(true){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_p: events::pause(); break;
                    case SDLK_LEFT: player.moveLeft(); break;
                    case SDLK_RIGHT: player.moveRight(); break;
                    default: break;
                }
            }
            if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        player.stop();
                    default: break;
                }
            }
            if(event.type == SDL_QUIT){
                events::finisher();
            }
        }
        computer.setAI(ball.shape);
        player.move(); computer.move();
        ball.move();
        int k=ball.check();
        if(k==1){
            ++a;
            return;
        }
        if(k==-1){
            ++b;
            return;
        }
        events::CLRSCR();
        ball.draw();
        player.draw();
        computer.draw();
        drawPoints(a,b);
        SDL_Flip(screen);
        if(a==10) events::Win();
        if(b==10) events::Lose();
        #ifdef _WIN32
        SDL_Delay(10);
        #else
        SDL_Delay(6);
        #endif // _WIN32
    }
}

int main ( int argc, char** argv ){
    events::starter();
    int i=0;
    while(true){
        Ball ball(i%2);
        gameloop(ball);
        ++i;
    }
    events::finisher();
    return 0;
}
