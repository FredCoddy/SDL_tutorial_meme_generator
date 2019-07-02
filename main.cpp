#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

void main_loop(SDL_Renderer *renderer);

int main(int argc, char *argv[])
{
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	win = SDL_CreateWindow("Cyril meme Generator !", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, 0);

	main_loop(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

	void main_loop(SDL_Renderer *renderer){
			while (1)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	}