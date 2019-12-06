main : main.o arithmetique.o
	gcc main.o arithmetique.o -o main
longueurMaximale : longueurMaximale.o filtabci.o element.o fonctionsCodage.o
	gcc longueurMaximale.o filtabci.o element.o fonctionsCodage.o -o longueurMaximale -lm
longueurMaximale.o : longueurMaximale.c
	gcc -c longueurMaximale.c
codeGold : codeGold.o filtabci.o element.o fonctionsCodage.o
	gcc codeGold.o filtabci.o element.o fonctionsCodage.o -o codeGold -lm
codeGold.o : codeGold.c
	gcc -c codeGold.c
filtabci.o : filtabci.c
	gcc -c filtabci.c
element.o : element.c
	gcc -c element.c
main.o : main.c
	gcc -c main.c
arithmetique.o : arithmetique.c
	gcc -c arithmetique.c
fonctionsCodage.o : fonctionsCodage.c
	gcc -c fonctionsCodage.c
all : main longueurMaximale codeGold
clean :
	rm *.o
