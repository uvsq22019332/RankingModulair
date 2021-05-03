run: main.exe
	./main.exe web1.txt 30

all: main.exe

main.exe: main.o matrice.o operation.o 
	gcc -o main main.o matrice.o operation.o -Wall

main.o: main.c operation.h
	gcc -c main.c -Wall -g 

matrice.o : matrice.c matrice.h
	gcc -c matrice.c -Wall -g 

operation.o : operation.c operation.h
	gcc -c operation.c -Wall -g 

clean :
	rm *.o
	rm main