#include "stddef.h"

typedef struct graphAdjMat {
    size_t numNodes;         /**< Numarul de noduri din graf */
    float **mat;             /**< Matricea de adiacenta */
} graphAdjMat_t;

typedef struct graphEdge {
    size_t u;           /**< Nodul sursa */
    size_t v;           /**< Nodul destinatie */
    float cost;         /**< Costul muchiei */
} graphEdge_t;

graphAdjMat_t *initGraph(size_t numNodes);

void insertEdge(graphAdjMat_t *g, size_t u, size_t v, float cost);

void freeGraph(graphAdjMat_t **g);

int isNeighbour(graphAdjMat_t *g, size_t u, size_t v);