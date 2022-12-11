# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c99
 
# Regula de compilare
build: quadtree

quadtree: quadtree.c
	$(CC) -o quadtree quadtree.c arbore.c $(CFLAGS)

# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
clean :
	rm -f quadtree
.PHONY : clean build
