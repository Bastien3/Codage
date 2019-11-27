main : main.o arithmetique.o
	gcc main.o arithmetique.o -o main
main.o : main.c
	gcc -c main.c
arithmetique.o : arithmetique.c
	gcc -c arithmetique.c
clean : 
	rm *.o
