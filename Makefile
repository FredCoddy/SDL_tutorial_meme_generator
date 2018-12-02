LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

main : main.o 
	g++ main.o  -o main $(LINKER_FLAGS)

main.o : main.cpp 
	g++ -c main.cpp  $(LINKER_FLAGS)  -o main.o  
