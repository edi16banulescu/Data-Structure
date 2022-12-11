In implementarea temei am folosit matricea de adiacenta cu structura si functiile in fisierul "graph_adj_matrix.c"
si "graph_adj_matrix.h".
Pentru rezolvarea primei cerinte am folosit algoritmul lui Djikstra in care creez o matrice de costuri unde costurile de 0
le notez cu macroul #INFINITY, in vectorul pred retin calea de la destinatie la sursa in ordine inversa, in vectorul distance
retin toate distantele de la sursa la fiecare nod, cu toate ca este necesar doar distanta pana la destinatie, iar vectorul 
visited ne spune daca nodul in care vrem sa ne deplasam a fost vizitat sau nu ( 0 sau 1 ). Pentru rezolvarea primului exercitiu
execut algoritmul de 2 ori pentru aflarea distantei de la sursa -> destinatie si de la destinatie - > sursa. Pentru afisarea
drumului parcurs iau 2 vectori, reversed si reversed_2, pe care ii inversez si ii concatenez in vectorul Path.