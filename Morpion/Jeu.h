#ifndef H_JEU
#define H_JEU


//Enumération des possibilités d'une case de jeu
enum Case {
    Vide = 0,
    Rond,
    Croix,
    Gagne
};

class Jeu {
    private:
        Case plateau[3][3];

        SDL_Texture *o, *x, *bg;

        Case tour, typegagne;

        bool fini;

        /*
        Victoire rond: (fini==true) && (typegagne==Rond);
        Victoire Croix: (fini==true) && (typegagne==Croix);
        Egalite (fini==true) && (typegagne==Vide);
        */

    public:
        //Constructeur/ Destructeur
        Jeu(int, int);
        ~Jeu();

        //Initialisation
        void viderJeu();

        bool init(SDL_Renderer *ren, int w, int h);

        void init_cases(SDL_Renderer *ren, int w, int h);

        void clic(SDL_Window *win, SDL_Renderer *ren, int, int, int, int);

        void aff(SDL_Window *win, SDL_Renderer *ren, int w, int h);

        void verifEnd(SDL_Window *win, SDL_Renderer *ren, int w, int h);

        SDL_Texture* loadTexture(char * filename, SDL_Renderer *ren);
};

#endif