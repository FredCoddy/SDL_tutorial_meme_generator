/*Test d'un jeu de Morpion, avec l'aide du tuto:
https://fearyourself.developpez.com/tutoriel/sdl/morpion/part1/

Compilation :  g++ main.cpp -o main -lSDL2 -lSDL2_image
*/

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Jeu.h"
using namespace std;


const int WIDTH  = 600;
const int HEIGHT = 600;


int main(int argc, char **argv){
    //Initialisation des variables, fenêtre et renderer
    Jeu jeu = Jeu(WIDTH, HEIGHT);
    SDL_Window *win = 0;
    SDL_Renderer *ren = 0;
    //Image de fond
    SDL_Texture* fond;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;

    SDL_Event event;
    int continuer = 0;

    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
		
        return 1;
    }
	
	
    // Création de la fenêtre
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
    SDL_SetWindowTitle(win, "Morpion" );

    //Fonction permettant de retourner une image en format texture
    fond = jeu.loadTexture("fond.jpg", ren);

    //Affichage fond
    //RenderCopy(texture a coller, texture cible, null=texture entiere, null=sur toute la texture cible)
    SDL_QueryTexture(fond, NULL, NULL, &pos.x, &pos.y );
    SDL_RenderCopy(ren, fond, NULL, NULL);
    SDL_RenderPresent(ren);
 
  
      if (!win || !ren) 
	 {
		cout << "Erreur à la création des fenêtres\n" << endl;
		SDL_Quit();
		return -1;
	 }

    jeu.init(ren, WIDTH, HEIGHT);

    //Boucle principale
    while(continuer==0){
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                //Si on veut quitter, done=1 suffira
                case SDL_QUIT:
                    continuer=1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    jeu.clic(win, ren, event.button.x, event.button.y, WIDTH, HEIGHT);
                     break;
                //Sinon on ne fait rien
                default:
                    break;
            }	
        }
        jeu.aff(win, ren, WIDTH, HEIGHT);
    }

    //LIbération mémoire
    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
	
    return 0;
}
