#include "events.h"

#ifdef _WIN32
    #define TEST
#endif // WIN32

void events::starter(){
    if(SDL_Init( SDL_INIT_EVERYTHING ) == -1){
        exit(1);
    }
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if(!screen){
        exit(2);
    }
    if(TTF_Init() == -1){
        exit(3);
    }
    if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1){
		exit(4);
	}
    font = TTF_OpenFont("resources/sans.ttf", 28);
    if(!font) exit(5);
	hit = Mix_LoadWAV("resources/hit.wav");
    if(!hit) exit(6);
    SDL_WM_SetCaption("Pong tennis",NULL);
    background.x=0; background.y=0; background.w=SCREEN_WIDTH; background.h=SCREEN_HEIGHT;
    message = TTF_RenderText_Shaded( font, "Press Space to start!", textColor , bgColor);
    graphics::apply_surface(30,SCREEN_HEIGHT/2-20,message,screen);
    SDL_Flip(screen);
    SDL_FreeSurface(message);
    while(1){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) exit(0);
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) return;
        }
	SDL_Delay(1);
    }
}
void events::finisher(){
    Mix_FreeChunk(hit);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}
void events::pause(){
    while(1){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) exit(0);
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) return;
        }
	SDL_Delay(1);
    }
}
void events::CLRSCR(){
    SDL_FillRect(screen,&background,SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
}

void events::WaitForExit(){
    while(1){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) return;
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) return;
        }
	SDL_Delay(1);
    }
}
void events::Win(){
    message = TTF_RenderText_Shaded( font, "You win", textColor , bgColor);
    graphics::apply_surface(30,SCREEN_HEIGHT/2-20,message,screen);
    SDL_Flip(screen);
    SDL_FreeSurface(message);
    events::WaitForExit();
    events::finisher();
}
void events::Lose(){
    message = TTF_RenderText_Shaded( font, "You lose", textColor , bgColor);
    graphics::apply_surface(30,SCREEN_HEIGHT/2-20,message,screen);
    SDL_Flip(screen);
    SDL_FreeSurface(message);
    events::WaitForExit();
    events::finisher();
}
