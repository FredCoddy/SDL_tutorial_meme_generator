#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include  <SDL2/SDL_gamecontroller.h>

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "img/goodEnough.jpg"

void main_loop(SDL_Rect dstrect, SDL_Renderer *renderer, SDL_Texture *img, SDL_Texture *texture);

int main(int argc, char *argv[])
{
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
	SDL_Color white = {255, 255, 255};
	int currentTime = 0, previousTime = 0;
	SDL_GameController *controller = SDL_GameControllerOpen(0);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	TTF_Init();

	win = SDL_CreateWindow("Cyril meme Generator !", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, 0);

	img = IMG_LoadTexture(renderer, IMG_PATH);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	TTF_Font *font = TTF_OpenFont("./fonts/impact.ttf", 30);
	SDL_Surface *surface = TTF_RenderText_Solid(font, "QUAND TU SAIS PAS QUOI DONNER COMME EXO", white);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 200;
	int texH = 200;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	SDL_Rect dstrect = {WIDTH / 2 - surface->w / 2, 25, texW, texH};

	main_loop(dstrect, renderer, img, texture);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

	TTF_Quit();
	SDL_Quit();
	return 0;
}

	void main_loop(SDL_Rect dstrect, SDL_Renderer *renderer, SDL_Texture *img, SDL_Texture *texture){
			while (1)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
			else if (e.key.keysym.sym == SDLK_DOWN)
			{
				dstrect.y++;
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				dstrect.y--;
			}
			else if (e.key.keysym.sym == SDLK_LEFT)
			{
				dstrect.x--;
			}
			else if (e.key.keysym.sym == SDLK_RIGHT)
			{
				dstrect.x++;
			}
			else if (e.type == SDL_CONTROLLERBUTTONDOWN){
				std::cout<<"coucou"<<std::endl;
			}
		}

		// currentTime = SDL_GetTicks();

		// if (currentTime - previousTime > 15)
		// {
		// 	dstrect.y++;
		// 	previousTime = currentTime;
		// }
		// if (dstrect.y > HEIGHT)
		// {
		// 	dstrect.y = 0;
		// }

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, img, NULL, NULL);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}
	}