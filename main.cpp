#include <SDL2/SDL.h>
#include <iostream>

using namespace std; 

void main_loop(){
    SDL_Event evenements;
    bool terminer(false);
    while(!terminer)
    {
	SDL_WaitEvent(&evenements);
		
	if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
	    terminer = true;
    }
}

int main(int argc, char **argv)
{	
    SDL_Window* fenetre(0);
    SDL_Init(SDL_INIT_VIDEO);
    

    fenetre = SDL_CreateWindow("Test Hello World SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    main_loop();
    SDL_Quit();
	
    return EXIT_SUCCESS;
}

