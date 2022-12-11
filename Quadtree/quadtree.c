#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arbore.h"

//Compresia
int uniform(RGB **grid, size_t size, double factor, TheRealTree ** node, size_t x, size_t y)
{
    long long mean = 0;
    long long red = 0, green = 0, blue = 0;
    size_t area = size * size;

    *node = malloc(sizeof(TheRealTree));
	(*node)->area = area;

    for(int i = x; i < x + size; i++)
        for(int j = y; j < y + size; j++)
        {
            red += grid[i][j].red;
            green += grid[i][j].green;
            blue += grid[i][j].blue;
        }

    red = red / area;
    green = green / area;
    blue = blue / area;

    (*node)->red = red;
    (*node)->green = green;
    (*node)->blue = blue;

    for(int i = x; i < x + size; i++)
        for(int j = y; j < y + size; j++)
        {
            mean += (red - grid[i][j].red) * (red - grid[i][j].red) + (green - grid[i][j].green) * (green - grid[i][j].green)
                        + (blue - (int)grid[i][j].blue) * (blue - grid[i][j].blue);
        }
        
    mean = mean / (3 * area);


    if(mean > factor)
    {
        uniform(grid, size / 2, factor, &(*node)->top_left, x, y);
        uniform(grid, size / 2, factor, &(*node)->top_right, x, y + (size / 2));
        uniform(grid, size / 2, factor, &(*node)->bottom_right, x + (size / 2), y + (size / 2));
        uniform(grid, size / 2, factor, &(*node)->bottom_left, x + (size / 2), y);
        return 1;
    }
    else
    {
        (*node)->top_right = NULL;
		(*node)->top_left = NULL;
		(*node)->bottom_left = NULL;
		(*node)->bottom_right = NULL;
        return 1;
    }
    return 0;    
}

//Decompresia
void decompression(QuadtreeNode * vector, RGB *** grid, int x, int y, int size, uint32_t *index)
{
	int i, j;

	if(vector[*index].top_left == -1 && vector[*index].top_right == -1 && vector[*index].bottom_right == -1 
                && vector[*index].bottom_left == -1)
	{
		for(i = y; i < y + size; i++)
			for(j = x; j < x + size; j++)
			{
				(*grid)[i][j].red = vector[*index].red;
				(*grid)[i][j].green = vector[*index].green;
				(*grid)[i][j].blue = vector[*index].blue;
			}
	}
	else
	{
        *index = *index + 1;
		decompression(vector, grid, x, y, size/2, index);
        *index = *index + 1;
		decompression(vector, grid, x + (size/2), y, size/2, index);
        *index = *index + 1;
		decompression(vector, grid, x + (size/2), y + (size/2), size / 2, index);
        *index = *index + 1;
		decompression(vector, grid, x, y + (size/2), size / 2, index);
	}
}

int main(int argc, char **argv) {

        if(strcmp(argv[1], "-c") == 0)
        {
            FILE *file_input = fopen(argv[argc - 2], "r");
            char header[2];
            int width, height, max_color;
            fscanf(file_input, "%s %d %d %d", header, &width, &height, &max_color);
            fscanf(file_input, " ");


            RGB **grid;
            grid = (RGB **) malloc (width * sizeof(RGB *));
            for(int i = 0; i < width; i++)
                grid[i] = calloc(height, sizeof(RGB));
            
            for(int i = 0; i < width; i++)
                for(int j = 0; j < height; j++)
                {
                    fscanf(file_input, "%c%c%c", &grid[i][j].red, &grid[i][j].green, &grid[i][j].blue);
                }

            double factor = atoi(argv[2]);
            TheRealTree * node = NULL;
            uniform(grid, width, factor, &node, 0, 0);

            uint32_t index = 0;
            //Quad-Tree-ul aka TheRealTree
            TheRealTree **vector_tree = malloc(sizeof(TheRealTree *));
            assign_vector(node, &vector_tree, &index);

            // vectorul indexat
            QuadtreeNode *vector = malloc(sizeof(QuadtreeNode) * index);
            copy_to_vector(vector_tree, &vector, index);

            uint32_t colors = 0;
            for(int i = 0; i < index; i++)
            {
                if(vector[i].bottom_right == -1)
                    colors++;
            }

            FILE *file_output = fopen(argv[argc - 1], "wb");
            fwrite(&colors, sizeof(uint32_t), 1, file_output);
            fwrite(&index, sizeof(uint32_t), 1, file_output);

            for(int i = 0; i < index; i++)
                fwrite(&vector[i], sizeof(QuadtreeNode), 1, file_output);

            fclose(file_output);
            fclose(file_input);

            //Eliberam memoria
            for(int i = 0; i < width; i ++)
                free(grid[i]);
            free(grid);

            for(int i = 0; i < index; i++)
			    free(vector_tree[i]);
		    free(vector_tree);
            free(vector);
        }


        if(strcmp(argv[1], "-d") == 0)
        {
            FILE *file_input = fopen(argv[argc - 2], "rb");
            FILE *file_output = fopen(argv[argc - 1], "w");

            uint32_t index, colors;
            fread(&colors, sizeof(int), 1, file_input);
			fread(&index,  sizeof(int), 1, file_input);


            QuadtreeNode *vector = malloc(index * sizeof(QuadtreeNode));
            fread(vector, sizeof(QuadtreeNode), index, file_input);
            uint32_t size = sqrt(vector[0].area);

            RGB **grid;
            grid = (RGB **) malloc (size * sizeof(RGB *));
            for(int i = 0; i < size; i++)
                grid[i] = calloc(size, sizeof(RGB));

            uint32_t current_index = 0;
            decompression(vector, &grid, 0, 0, size, &current_index);

            fprintf(file_output, "P6\n");
	        fprintf(file_output, "%d %d\n", size, size );
	        fprintf(file_output, "255\n");
	
	        for(int i = 0; i < size; i++)
		        fwrite(grid[i], sizeof(RGB), size, file_output);

            //Eliberam memoria
            for(int i = 0; i < size; i ++)
                free(grid[i]);
            free(grid);
            free(vector);

            fclose(file_input);
            fclose(file_output);
        }


    return 0;
}

