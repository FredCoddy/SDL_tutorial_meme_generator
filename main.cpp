#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "img/goodEnough.jpg"

int main(int argc, char *argv[])
{

	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
	int w, h; // texture width & height
	int scale = 6;
	int currentTime, previousTime;

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	TTF_Init();

	win = SDL_CreateWindow("Cours inversé test TTF",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH,HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, 0);

	img = IMG_LoadTexture(renderer, argv[1]);
	SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
											   // put the location where we want the texture to be drawn into a rectangle
											   // I'm also scaling the texture 2x simply by setting the width and height
											   // SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w= w/scale; texr.h = h/scale;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	TTF_Font *font = TTF_OpenFont("./fonts/impact.ttf", 30);
	const char *error = TTF_GetError();
	SDL_Color white = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font, "QUAND TU SAIS PAS QUOI DONNER COMME EXO", white);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);


	int texW = 200;
	int texH = 200;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	
	std::cout<< surface->h <<std::endl;
	SDL_Rect dstrect = {WIDTH/2 -  surface->w/2, 25, texW, texH};

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

		currentTime = SDL_GetTicks();

		if (currentTime - previousTime > 30){
			dstrect.y++;
			previousTime = currentTime;
		}
		if (dstrect.y > HEIGHT){
			dstrect.y =0;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, img, NULL, NULL);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	// SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	// SDL_DestroyWindow(win);

	TTF_Quit();
	SDL_Quit();
	return 0;
}
