#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Jeu.h"
using namespace std;

//Déclaration coordonnées en pixel des cases
vector<int> pos_x;

vector<int> pos_y; 

Jeu::Jeu(int w, int h){

    viderJeu();

    o = NULL;
    x = NULL;
    bg = NULL;

   //Création de vecteurs de coordonnées en pixels
    for (int c = 0; c<3 ; c++){
        for (int x = 0; x<w; x+= w/3){
            pos_x.push_back(x);
        }
    }
    for (int y = 0; y<h; y+= h/3){
        for (int l = 0; l<3 ; l++){
            pos_y.push_back(y);
        }
    }
}

//Destructeur : libération mémoire
Jeu::~Jeu(){
    SDL_DestroyTexture(o);
    SDL_DestroyTexture(x);
    SDL_DestroyTexture(bg);
}

//Vide le dernier plateau et initialise une partie
void Jeu::viderJeu(){
    int x, y;
    for(x=0; x<3; x++){
        for (y=0; y<3; y++){
            plateau[x][y] = Vide;
        }
    }
    tour = Rond;
    fini = false;
}

// Chargement des images dans les surfaces
bool Jeu::init(SDL_Renderer *ren, int w, int h){
    cout << "Initialisation" <<endl;
    //Vérification alloc
    if(o!=NULL){
        SDL_DestroyTexture(o), o = NULL;
    }
    if(x!=NULL){
        SDL_DestroyTexture(x), x = NULL;
    }
    if(bg!=NULL){
        SDL_DestroyTexture(bg), bg = NULL;
    }

    //Images
    o = loadTexture("rond.png", ren);
    x = loadTexture("croix.png", ren);
    bg = loadTexture("background.png", ren);
    if( (o==NULL) || (x==NULL) || (bg==NULL)){
        cout << "Problème de chargement d'une image" << endl;
        return false;
    }
    //Init premier joueur
    tour = Rond;

    init_cases(ren, w, h);

/*
    //Mise en place de la transparence SDL1.2
    if(SDL_SetColorKey(o,SDL_SRCCOLORKEY,0)==-1)
        cout << "Erreur avec la transparence du rond" << endl;
 
    if(SDL_SetColorKey(x,SDL_SRCCOLORKEY,0)==-1)
        cout << "Erreur avec la transparence de la croix" << endl;*/
 
    return true;
}

//Remet les cases à vide sans croix ni ronds
void Jeu::init_cases(SDL_Renderer *ren, int w, int h){
    int w_case = w/3, h_case= h/3;
    SDL_Rect DestR;
    DestR.x = 0;
    DestR.y = 0;
    DestR.w = w_case;
    DestR.h = h_case;


    //Affichage cases vides
    for (int i = 0; i < pos_x.size(); i++){
        DestR.x = pos_x[i];
        DestR.y = pos_y[i];
        SDL_RenderCopy(ren, bg, NULL, &DestR);
        SDL_RenderPresent(ren);
    }
}

//Affiche le plateau
void Jeu::aff(SDL_Window *win, SDL_Renderer *ren, int w, int h){
    //Dimension case
    int w_case = w/3, h_case= h/3;
    //Initialisation de l'objet contenant les positions des cases
    SDL_Rect DestR;
    DestR.x = 0;
    DestR.y = 0;
    DestR.w = w_case-5;
    DestR.h = h_case-5;

    for (int i = 0; i < pos_x.size(); i++){
        //Récupération position case actuelle
        DestR.x = pos_x[i];
        DestR.y = pos_y[i];
        switch(plateau[DestR.y/DestR.h][DestR.x/DestR.w]){
            case Croix:
                SDL_RenderCopy(ren, x, NULL, &DestR);break;
            case Rond:
                SDL_RenderCopy(ren, o, NULL, &DestR);break;
            //Si la partie est gagnée, affichage message puis remise à zéro
            case Gagne:
                if (typegagne==Rond) {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Gagné!", "Rond a gagné! Félicitations", win);
                    viderJeu();
                    init_cases(ren,w,h);
                    }
                else {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Gagné!", "Croix a gagné! Félicitations", win);
                    viderJeu();
                    init_cases(ren,w,h);
                    }
                break;
            default:
            break;
        }
        //Rafraichissement écran
        SDL_RenderPresent(ren);
    }

}

void Jeu::clic(SDL_Window *win, SDL_Renderer *ren, int x, int y, int w, int h){

    if(fini){
        viderJeu();
    }else{
        //Dimension case
        int w_case = w/3;
        int h_case = h/3;

        //Position case
        int i = y/h_case;
        int j = x/w_case;

        if(plateau[i][j]==Vide){
            plateau[i][j] = tour;
            tour = (tour==Rond)?Croix:Rond;
        }  
    }
    verifEnd(win, ren, w, h);

}

//Vérifie les conditions de victoire ou  égalité
void Jeu::verifEnd(SDL_Window *win, SDL_Renderer *ren, int w, int h){
    bool casevide = false;
    int i;

    //Test lignes
    for (i=0;i<3; i++){
        if (plateau[i][0]!=Vide){
            if((plateau[i][0]==plateau[i][1]) && (plateau[i][0]==plateau[i][2])){
                fini = true;
                typegagne = plateau[i][0];
                plateau[i][0] = Gagne;
                plateau[i][1] = Gagne;
                plateau[i][2] = Gagne;
            }
        }else
            casevide = true;
    }

    //Test Colonnes
	for(i=0;i<3;i++)
	{
		if( plateau[0][i]!=Vide ){
			if((plateau[0][i]==plateau[1][i]) && (plateau[0][i]==plateau[2][i])){
				fini = true;
				typegagne = plateau[0][i];
				plateau[0][i] = Gagne;
				plateau[1][i] = Gagne;
				plateau[2][i] = Gagne;
			}
		}
		else
			casevide = true;
	}

    //Test diagonale
    if( plateau[0][0]!=Vide ){
        if ( (plateau[0][0]==plateau[1][1]) && (plateau[0][0]==plateau[2][2])){
            fini = true;
            typegagne = plateau[0][0];
            plateau[0][0] = Gagne;
            plateau[1][1] = Gagne;
            plateau[2][2] = Gagne;
        }
    }
    else
        casevide = true;

    if(plateau[2][0]!=Vide){
        if ( (plateau[0][2]==plateau[1][1]) && (plateau[0][2]==plateau[2][0])){
            fini = true;
            typegagne = plateau[0][2];
            plateau[0][2] = Gagne;
            plateau[1][1] = Gagne;
            plateau[2][0] = Gagne;
        }
    }
    else
        casevide = true;
    
    //Verifier si cases vides
    if( (plateau[1][1] == Vide)||(plateau[1][2] == Vide)||
        (plateau[2][1] == Vide)||(plateau[2][2] == Vide))
        casevide = true;
 
    fini = !casevide || fini;
    //Si aucun gagnant (i.e plus de case vide), remise à zéro du jeu
    if(!casevide){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Egalité", "Relancer partie", win);
        viderJeu();
        init_cases(ren,w,h);
    }
}

//Permet de charger une image et la transformer en Texture
SDL_Texture* Jeu::loadTexture(char * filename, SDL_Renderer *ren){
        SDL_Texture *texture = 0;
        texture = IMG_LoadTexture(ren, filename);
        if (!texture)
          {
          cout << "Erreur chargement image : %s\n" << SDL_GetError() << endl;
          return 0;
          }
        return texture;
}