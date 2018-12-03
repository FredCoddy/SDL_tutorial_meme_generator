LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

main : main.o Jeu.o
	g++ main.o Jeu.o -o main $(LINKER_FLAGS)

main.o : main.cpp 
	g++ -c main.cpp $(LINKER_FLAGS)  -o main.o  

Jeu.o : Jeu.cpp Jeu.h
	g++ -c Jeu.cpp $(LINKER_FLAGS) -o Jeu.o
