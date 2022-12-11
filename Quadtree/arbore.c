#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "arbore.h"

int assign_vector(TheRealTree * node, TheRealTree *** vector, uint32_t * index)
{
	if(node != NULL)
	{
        if((*index) > 0)
      		(*vector) = realloc((*vector), sizeof(QuadtreeNode*) * ((*index) + 1));
        
        (*vector)[(*index)] = node;
        node->index = *index;
        *index = *index + 1;

        assign_vector(node->top_left, vector, index);
        assign_vector(node->top_right, vector, index);
        assign_vector(node->bottom_right, vector, index);
        assign_vector(node->bottom_left, vector, index);
	}
	else
    {
		return 1;
    }
    return 0;
}

//Functie pentru creearea vectorului indexat pentru rezolvarea cerintelor
void copy_to_vector(TheRealTree ** vector_tree, QuadtreeNode ** vector, uint32_t index)
{
	
	for(int i = 0; i < index; i++)
	{
		(*vector)[i].red = vector_tree[i]->red;
		(*vector)[i].blue = vector_tree[i]->blue;
		(*vector)[i].green = vector_tree[i]->green;
		(*vector)[i].area  = vector_tree[i]->area;
	
		if(vector_tree[i]->top_left == NULL)
			(*vector)[i].top_left = -1;
		else
			(*vector)[i].top_left = vector_tree[i]->top_left->index;

		if(vector_tree[i]->top_right == NULL)	
			(*vector)[i].top_right = -1;
		else
			(*vector)[i].top_right = vector_tree[i]->top_right->index;

		if(vector_tree[i]->bottom_right == NULL)	
			(*vector)[i].bottom_right = -1;
		else
			(*vector)[i].bottom_right = vector_tree[i]->bottom_right->index;

		if(vector_tree[i]->bottom_left == NULL)	
			(*vector)[i].bottom_left  = -1;
		else
			(*vector)[i].bottom_left = vector_tree[i]->bottom_left->index;

	}
}