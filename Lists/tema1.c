#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "liste.h"

void e1(list_t *list)
{
    //creez o copie pe care lucrez, insa o sa elimin din lista originala
    list_t *cpy = init_list();
    node_t *p = list->head;
    int position = 0;
    while(p != NULL)
    {
        insert_node(cpy, p->value, p->timestamp, position);
        position++;
        p = p->next;
    }

    double k = 5;
    double average;
    double deviation;
    double nod_mijloc;
    int curent = 2;
    p = cpy->head->next->next;

    while(p != cpy->tail->prev)
    {
        average = 0;
        deviation = 0;
        nod_mijloc = p->value;

        average = p->prev->prev->value + p->prev->value + p->value + p->next->value + p->next->next->value;
        average = average / k;

        deviation = pow((p->prev->prev->value - average), 2) + pow((p->prev->value - average), 2)
                                    + pow((p->value - average), 2) + pow((p->next->value - average), 2)
                                                                + pow((p->next->next->value - average), 2);
        deviation = sqrt(deviation / k);

        p = p->next;
        if(nod_mijloc > (average + deviation) || nod_mijloc < (average - deviation))
            remove_node(list, curent);
        else
            curent++;
    }

    destroy_list(cpy);
}

list_t *e2(list_t *list)
{
    node_t *p = list->head->next->next;

    // valorile medianelor vor fii stocate in "mediane"
    list_t *mediane = init_list();
    int i;
    int position = 0;

    for(i = 2; i < list->len - 2; i++)
    {
        // creez o fereastra temporara sortata
        list_t *tmp = init_list();
        insert_node(tmp, (p->prev->prev->value), (p->prev->prev->timestamp), 0);
        insert_node(tmp, (p->prev->value), (p->prev->timestamp), 1);
        insert_node(tmp, (p->value), (p->timestamp), 2);
        insert_node(tmp, (p->next->value), (p->next->timestamp), 3);
        insert_node(tmp, (p->next->next->value), (p->next->next->timestamp), 4);
        sort(tmp);

        insert_node(mediane, tmp->head->next->next->value, p->timestamp, position);
        position++;

        destroy_list(tmp);
        p = p->next;
    }
    return mediane;
}

list_t *e3(list_t *list)
{
    double k = 5;
    double average;
    int position = 0;

    node_t *p = list->head->next->next;

    list_t *media_aritmetica = init_list();

    while(p != list->tail->prev)
    {
        average = 0;
        average = p->prev->prev->value + p->prev->value + p->value + p->next->value + p->next->next->value;
        average = average / k;

        insert_node(media_aritmetica, average, p->timestamp, position);
        position++;

        p = p->next;
    }
    return media_aritmetica;
}

void u(list_t *list)
{
    node_t *p = list->head->next;

    for(int i = 1; i < list->len; i++)
    {
        if((p->timestamp - p->prev->timestamp >= 100) && (p->timestamp - p->prev->timestamp <= 1000))
        {
            p->timestamp = (p->timestamp + p->prev->timestamp) / 2;
            p->value = (p->value + p->prev->value) / 2;
        }

        p = p->next;
    }
}

void c(list_t *list)
{
    //creez w
    list_t *w = init_list();

    double sum = 0;
    int aux_timestamp = 0;
    for(int i = 0; i < 3; i++)
        sum = sum + pow(i / (3.0 - 1), 2) * 0.9 + 0.1;

    for(int i = 0; i < 3; i++)
    {
        double aux = pow(i / (3.0 - 1), 2) * 0.9 + 0.1;
        aux = aux / sum;

        insert_node(w, aux, aux_timestamp, i);
    }

    node_t *p = list->head->next->next->next;

    for(int i = 3; i < list->len - 3; i++)
    {
        if(p->timestamp - p->prev->timestamp > 1000)
        {
            list_t *left = init_list();
            list_t *right = init_list();

            // creez left
            for(int j = i - 3; j < i; j++)
                insert_node(left, get_nth_node(list, j)->value, get_nth_node(list, j)->timestamp, left->len);

            // creez right
            for(int j = i; j < i + 3; j++)
                insert_node(right, get_nth_node(list, j)->value, get_nth_node(list, j)->timestamp, 0);


            aux_timestamp = p->prev->timestamp + 200;
            while(aux_timestamp < p->timestamp)
            {
                double factor = (double)(aux_timestamp - get_nth_node(left, 2)->timestamp)
                                         / (get_nth_node(right, 2)->timestamp - get_nth_node(left, 2)->timestamp);
                double formula = 0.0;

                for(int j = 0; j < 3; j++)
                {
                    formula += (1.0 - factor) * (get_nth_node(left, j)->value * get_nth_node(w, j)->value) 
                                                        + factor * get_nth_node(right, j)->value * get_nth_node(w,j)->value;
                }
                insert_node(list, formula, aux_timestamp, i);
                i++;
                aux_timestamp += 200;
            }
            destroy_list(left);
            destroy_list(right);
        }
        
        p = p->next;
    }
    destroy_list(w);
}

int st(list_t *list, int delta)
{
    sort(list);
    node_t *p = list->head;
    int interval = p->value;

    // creez inceputul intervalului
    while(interval % delta != 0)
        interval--;

    while(p != NULL)
    {
        int length = 0;
        while(p->value < (double)(interval + delta))
        {
            length++;
            if(p->next != NULL)
                p = p->next;
            else if(p->next == NULL)
                {
                    printf("[%d, %d] %d\n", interval, interval + delta, length);
                    return 0;
                }
                else
                    return 0;
        }

        if(length != 0)
            printf("[%d, %d] %d\n", interval, interval + delta, length);

        interval += delta;
    }

    return 0;
}

int main(int argc, char **argv) {

    list_t *list = init_list();

    read_list(list);

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--e1") == 0)
        {
            e1(list);
        }   
        else if(strcmp(argv[i], "--e2") == 0)
        {
            list_t *mediane = e2(list);
            destroy_list(list);
            list = mediane;
        }
        else if(strcmp(argv[i], "--e3") == 0)
        {
            list_t *media_aritmetica = e3(list);
            destroy_list(list);
            list = media_aritmetica;
        }
        else if(strcmp(argv[i], "--u") == 0)
        {
            u(list);
        }
        else if(strcmp(argv[i], "--c") == 0)
        {
            c(list);
        }
        else if(strncmp(argv[i], "--st", 4) == 0)
        {
            int delta = atoi(argv[i] + 4);
            st(list, delta);
            destroy_list(list);
            return 0;
        }
    }
    print_list(list);
    destroy_list(list);

    return 0;
}