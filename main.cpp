#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char **argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window *window = SDL_CreateWindow("Cours inversé test TTF",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	TTF_Font *font = TTF_OpenFont("/home/coddy/.fonts/arial.ttf",30);
	const char *error = TTF_GetError();
	SDL_Color white = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font,"Coucou Bioinfo", white);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);

	int texW = 200;
	int texH = 200;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		SDL_Rect dstrect = {300, 200, texW, texH};
        SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}