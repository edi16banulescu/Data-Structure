#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"

list_t *init_list() 
{
    list_t *new_list = malloc(sizeof(list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;

    return new_list;
}

void destroy_list(list_t *list) 
{
    node_t *aux;

    while (list->len > 0) {
        aux = list->tail;
        list->tail = list->tail->prev;
        free(aux);
        --list->len;
    }

    free(list);
}

void print_list(list_t *list) 
{
    node_t *aux = list->head;
    printf("%lu\n", list->len);

    if (aux == NULL) {
        // Lista vida
        printf("NULL\n");
        return;
    }

    while (aux != list->tail) {
        printf("%d %.2f\n", aux->timestamp, aux->value);
        aux = aux->next;
    }
    printf("%d %.2f\n", aux->timestamp, aux->value);
}

int insert_node(list_t *list, double value, int timestamp, int position) 
{
    if(position < 0 || (position > list->len && list->len != 0))
        return -1;
    
    node_t *nou = malloc(sizeof(node_t));
    nou->next = NULL;
    nou->prev = NULL;
    nou->value = value;
    nou->timestamp = timestamp;

    if(list->head == NULL)
    {
        list->head = nou;
        list->tail = nou;
        list->len += 1;
        return 0;
    }

    if(position == 0)
    {
        nou->next = list->head;
        list->head->prev = nou;
        list->head = nou;
        list->len += 1;
        return 0;
    }

    if(position == list->len)
    {
        list->tail->next = nou;
        nou->prev = list->tail;
        list->tail = nou;
        list->len += 1;
        return 0;
    }

    int curent = 0;
    node_t *q = list->head;
    while(q->next != NULL && position != curent)
    {
        q = q->next;
        curent++;
    }

    nou->next = q;
    nou->prev = q->prev;
    q->prev->next = nou;
    q->prev = nou;
    list->len += 1;

    return 0;
}

int remove_node(list_t *list, int position) 
{
    if(position < 0 || (position > list->len && list->len != 0))
        return -1;
    node_t *p;

    p = list->head;

    if(position == 0)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
        list->len -= 1;
        free(p);
        return 0;
    }

    p = list->tail;

    if(position == list->len - 1)
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->len -= 1;
        free(p);
        return 0;
    }

    int curent = 0;
    p = list->head;
    while(p->next != NULL && position != curent)
    {
        p = p->next;
        curent++;
    }

    p->next->prev = p->prev;
    p->prev->next = p->next;
    free(p);
    list->len -= 1;

    return 0;
}

node_t* get_nth_node(list_t *list, size_t n)
{
    if (!list || n >= list->len || n < 0) {
        return NULL;
    }

    node_t* tmp = list->head;

    while (n--) {
        tmp = tmp->next;
    }

    return tmp;
}

void sort(list_t *list)
{
    if(list->head == NULL)
        return;

    for(int i = 0; i < list->len - 1; i++) 
    {
        node_t *n1 = get_nth_node(list, i);
        for(int j = i + 1; j < list->len; j++)
        {
            node_t *n2 = get_nth_node(list, j);
            if(n1->value > n2->value)
            {
                double tmp;
                tmp = n1->value;
                n1->value = n2->value;
                n2->value = tmp;
            }
        }
    }
}

list_t *read_list(list_t *list)
{
    int timestamp;
    double value;
    int numarPerechi;
    int position = 0;

    scanf("%d\n", &numarPerechi);

    while (position < numarPerechi)
    {
        scanf("%d %lf", &timestamp, &value);
        insert_node(list, value, timestamp, position);
        position++;
    }

    return list;
}