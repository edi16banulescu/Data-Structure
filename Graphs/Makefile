# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c99
 
# Regula de compilare
build: tema3

tema3: tema3.c
	$(CC) -o tema3 tema3.c graph_adj_matrix.c $(CFLAGS)

# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
clean:
	rm -f tema3

run: tema3
	./tema3

.PHONY : clean build
