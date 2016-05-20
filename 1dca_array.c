/**
 * Anne Chen
 * CS 11, Spring 2016 Lab 5  
 * 
 * This program simulates a one dimensional cellular automaton. This is
 * a collection of cells that hold data values, organized into geometric
 * arrangements. This 1DCA has two states, full and empty. It updates 
 * over time according to the following pattern:
 * 
 *   1. If the current cell is empty, and one of the two adjacent cells 
 *      is full (but not both), set the current cell to be full.
 * 
 *   2. Otherwise set the current cell to be empty.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "memcheck.h"

/*
 *  Generates a random value (0 or 1).  
 */

int random_generate(void)

{
    int i;
    i = rand() % 2;
    return i;
}

/* Generates the array. */


int *line_generate(int cells)

{
    int i;
    int *array;

    array = (int *)malloc(sizeof(int) * cells);

    if (array == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        free(array);
        exit(1);
    }

    /* generate cells randomly */
    for (i = 0; i < cells; i++) {
        if (i == 0 || i == (cells - 1)) {
            array[i] = 0;
        }
        else {
            array[i] = random_generate();
        }
    }
    return array;
}

/* 
 * Prints the line generated. 
 */

int line_print(int i)

{
    if (i == 0) {
        printf(".");
    }
    if (i == 1) {
        printf("*");
    }
    return 0;
}

/* 
 * Updates the array according to the following pattern:
 * 
 *   1. If the current cell is empty, and one of the two adjacent cells 
 *      is full (but not both), set the current cell to be full.
 * 
 *   2. Otherwise set the current cell to be empty.
 */

int line_update(int cells, int *array)
{
    int i;
    int *temp_array;
    temp_array = (int *)malloc(sizeof(int) * cells);
    
    /* initialize array to be all 0 */
    for (i = 0; i < cells; i++) {
        temp_array[i] = 0;
    }

    for (i = 1; i < cells - 1; i++) {
        if (array[i] == 0) {
            if (array[i - 1] == 1 ^ array[i + 1] == 1) {
                temp_array[i] = 1;
            }
        }
    }
    
    for (i = 0; i < cells; i++) {
        array[i] = temp_array[i];
    }
    
    free(temp_array);

    return 0;  
}

/* 
 * Return the line generated and updates it for a number of generations
 * based on the command line input.
 */

int main(int argc, char *argv[])

{
    int *temp_array;
    int cells, gen;
    int j, k, t;
    srand(time(0));
    
    if (argc != 3) {
        fprintf(stderr, "Error! Invalid number of arguments given.\n");
        exit(1);
    }

    cells = atoi(argv[1]);
    gen = atoi(argv[2]);
	
    temp_array = (int*)malloc(cells * sizeof(int));
	
    if (temp_array == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }
    
    temp_array[0] = 0;
    temp_array[cells - 1] = 0;
	
    for (t = 1;t < (cells - 1); t++) {
        temp_array[t] = (rand() % 2);
    }
    
    for (j = 0; j < gen; j++) {
        for (k = 0; k < cells; k++) {
            line_print(temp_array[k]);
        }
        printf("\n");
        line_update(cells, temp_array);
    }
    
    free(temp_array);
    
    print_memory_leaks();
    return 0;
}
