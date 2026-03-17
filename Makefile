rubiks.out: rubiks.o glad.o
	gcc rubiks.o glad.o -o rubiks.out -lSDL2 -lGL -ldl -lm -I include


rubiks.o: rubiks.c
	gcc -c rubiks.c -I include


glad.o: glad.c
	gcc -c glad.c -I include