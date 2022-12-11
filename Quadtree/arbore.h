#include <stdlib.h>
#include <inttypes.h>

typedef struct QuadtreeNode {
    unsigned char blue, green, red;
    __uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) QuadtreeNode;

typedef struct RGB {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

//In aceasta structura vom crea arborele propriu-zis
typedef struct TheRealTree {
	
	unsigned char blue, green, red;
	long long index;	
	uint32_t area;

	struct TheRealTree *top_left, *top_right;
	struct TheRealTree *bottom_left, *bottom_right;
 
} TheRealTree;

int assign_vector(TheRealTree * node, TheRealTree *** vector, uint32_t * index);

void copy_to_vector(TheRealTree ** vector_tree, QuadtreeNode ** vector, uint32_t index);