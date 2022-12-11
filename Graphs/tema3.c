#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_adj_matrix.h"
#define INFINITY 9999

void e1(graphAdjMat_t *g, int start, int destination, float *total_cost) 
{
    float **cost, *distance, *pred, mindistance;
    int *visited, count, nextnode, i, j;

    //cost matrix which is almost the same as g->mat
    cost = malloc(g->numNodes * sizeof(float *));
    for(i = 0; i < g->numNodes; i++)
        cost[i] = calloc(g->numNodes, sizeof(float));

    //distance stores the distance between points
    distance = malloc(g->numNodes * sizeof(float));

    //pred[] stores the predecessor of each node
    pred = malloc(g->numNodes * sizeof(float));

    //visited is a boolean vector: 1 - visited; 0 - not
    visited = malloc(g->numNodes * sizeof(int));
    printf("%d\n", destination);

    //create the cost matrix
    for (i = 0; i < g->numNodes; i++)
        for (j = 0; j < g->numNodes; j++)
            if (g->mat[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = g->mat[i][j];

    //initialize
    for (i = 0; i < g->numNodes; i++)
    {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    //current node
    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    //count gives the number of nodes seen so far
    while (count < g->numNodes - 1)
    {
        mindistance = INFINITY;

        //nextnode gives the node at minimum distance
        for (i = 0; i < g->numNodes; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        //check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < g->numNodes; i++) 
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    // printing the distance
    printf("%.1f ", distance[destination]);

    // creating the path
    int Path[10];
    int reversed[10];
    int k = 0;
    reversed[k] = destination;
    j = destination;
    do
    {
        k++;
        j = pred[j];
        reversed[k] = j;
    } while (j != start);
    k++;
    reversed[k] = start;
    int c = 0;
    for(i = k - 1; i >= 0; i--)
    {
        Path[c] = reversed[i];
        c++; 
    }

    //add at total_cost
    *total_cost += distance[destination];

    //backwards for destination->source
    for (i = 0; i < g->numNodes; i++)
    {
        distance[i] = cost[destination][i];
        pred[i] = destination;
        visited[i] = 0;
    }

    distance[destination] = 0;
    visited[destination] = 1;
    count = 1;

    while (count < g->numNodes - 1)
    {
        mindistance = INFINITY;

        for (i = 0; i < g->numNodes; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < g->numNodes; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    //printing the distance
    printf("%.1f\n", distance[start]);

    //creating the second path
    int reversed_2[10];
    int z = 0;
    j = start;
    do
    {
        reversed_2[z] = j;
        j = pred[j];
        k++;
        z++;
    } while (j != destination);

    int cz = z;
    for(i = k - 1; i > k - 1 - cz; i--)
    {
        z--;
        Path[c] = reversed_2[z];
        c++;
    }

    //printing path
    for(i = 0; i < k - 1; i++)
        printf("%d ", Path[i]);
    printf("%d\n", Path[k - 1]);

    //add at total_cost
    *total_cost += distance[start];

    //free vectors
    free(pred);
    free(visited);
    free(distance);
    for(i = 0; i < g->numNodes; i++)
        free(cost[i]);

    free(cost);
}

int main() {
    int n, m, d;
    fscanf(stdin, "%d %d %d", &n, &m, &d);
    graphEdge_t *edge = malloc (sizeof(graphEdge_t));
    graphAdjMat_t *g = initGraph(n);
    int i = 0;

    //create matrix
    while(i < m)
    {
        fscanf(stdin, "%zu %zu %f", &(edge->u), &(edge->v), &(edge->cost));
        insertEdge(g, edge->u, edge->v, edge->cost);
        i++;
    }

    int *depozit = malloc(d * sizeof(int));
    i = 0;
    while(i < d)
    {
        fscanf(stdin, "%d", &depozit[i]);
        i++;
    }

    int nr_tasks;
    fscanf(stdin, "%d", &nr_tasks);

    i = 0;
    char task[2];
    while(i < nr_tasks)
    {
        fscanf(stdin, "%s[^\n]", task);
        if(strcmp(task, "e1") == 0)
        {
            float total_cost = 0;
            int start;
            fscanf(stdin, "%d", &start);
            int nr_magazine;
            fscanf(stdin, "%d", &nr_magazine);
            int j = 0;
            while(j < nr_magazine)
            {
                int destination;
                fscanf(stdin, "%d", &destination);
                e1(g, start, destination, &total_cost);
                j++;
            }
            printf("%.1f", total_cost);
        }
        i++;
        if(i != nr_tasks)
            printf("\n");
    }

    //free
    free(depozit);
    freeGraph(&g);
    free(edge);
    return 0;
}