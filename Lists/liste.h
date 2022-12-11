#include <stdlib.h>

typedef struct node
{
    int timestamp;
    double value;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct List
{
    node_t *head;
    node_t *tail;
    size_t len;
} list_t;

list_t *init_list();

void destroy_list(list_t *list);

void print_list(list_t *list);

int insert_node(list_t *list, double value, int timestamp, int position);

int remove_node(list_t *list, int position);

node_t* get_nth_node(list_t *list, size_t n);

void sort(list_t *list);

list_t *read_list(list_t *list);