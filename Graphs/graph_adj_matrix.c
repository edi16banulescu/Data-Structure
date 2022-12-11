#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "graph_adj_matrix.h"

graphAdjMat_t *initGraph(size_t numNodes) {
    if (numNodes <= 0) {
        printf("initGraph: numarul de noduri trebuie sa fie un numar pozitiv nenul\n");
        return NULL;
    }

    graphAdjMat_t *g = malloc(sizeof(graphAdjMat_t));

    g->numNodes = numNodes;
    g->mat = malloc(numNodes * sizeof(int *));

    for (int i = 0; i < numNodes; i++) {
        g->mat[i] = calloc(numNodes, sizeof(int));
    }
    return g;
}


void insertEdge(graphAdjMat_t *g, size_t u, size_t v, float cost) {
    if (g == NULL) {
        printf("insertEdge: Graful este NULL\n");
        return;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("insertEdge: perechea de noduri (%zu, %zu) este invalida pentru un graf cu %zu noduri\n", u, v, g->numNodes);
        return;
    }

    if (isNeighbour(g, u, v)) {
        printf("Muchia (%zu, %zu) de cost %f exista deja in graf. Noul cost va fi %f\n", u, v, g->mat[u][v], cost);
    }

    /* Inserez noua muchie */
    g->mat[u][v] = cost;
}

void freeGraph(graphAdjMat_t **g) {
    if (*g == NULL) {
        return;
    }

    /* Eliberez matricea de adiacenta */
    for (size_t u = 0; u < (*g)->numNodes; u++) {
        free((*g)->mat[u]);
    }
    free((*g)->mat);

    /* Eliberez structura */
    free(*g);
    *g = NULL;
}

int isNeighbour(graphAdjMat_t *g, size_t u, size_t v) {
    if (g == NULL) {
        printf("isNeighbour: Graful este NULL\n");
        return -1;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("isNeighbour: perechea de noduri (%zu, %zu) este invalida pentru un graf cu %zu noduri\n", u, v, g->numNodes);
        return -1;
    }

    return g->mat[u][v] != 0;
}