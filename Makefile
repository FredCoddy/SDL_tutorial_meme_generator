exec: main.o
	gcc main.o -o exec

main.o: main.c
	gcc -c -g main.c

lancer: exec
	./exec