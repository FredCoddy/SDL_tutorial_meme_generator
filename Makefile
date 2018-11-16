main : main.o 
	g++ main.o  -o main `sdl2-config --libs`

main.o : main.cpp 
	g++ -c main.cpp  -o main.o  
