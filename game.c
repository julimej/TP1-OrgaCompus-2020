#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cells_grid.h"
/* add to a width index, wrapping around like a cylinder */

int xadd (int i, int a,int width) {
	i += a;
	while (i < 0) i += width;
	while (i >= width) i -= width;
	return i;
}

/* add to a height index, wrapping around */

int yadd (int i, int a, int height) {
	i += a;
	while (i < 0) i += height;
	while (i >= height) i -= height;
	return i;
}

/* return the number of on cells adjacent to the i,j cell */

int vecinos(unsigned char* board, unsigned int i, unsigned int j, unsigned int rows, unsigned int columns) {
	int	count = 0;

	for (int k=-1; k<=1; k++) {
        for (int l=-1; l<=1; l++) {
            if ((i + k + (i*columns) + j + l + (j*rows)) < 0 || (i + k + (i*columns) + j + l + (j*rows)) > rows*columns) {
                printf("Afuera con numero = %d\n", i + k + (i*columns) + j + l + (j*rows));
            } 
            if (k || l) {
                printf("%d\n",i + k + (i*columns) + j + l + (j*rows));
                // if (board[(i+k) * columns + j + l]) count++;
            }
        }
        printf("\n\n");
    }
	return count;
}

void play (int width, int height, char** board) {

	int	a;

    char** newboard = (char**)calloc(width, sizeof(char*));

    for (int index=0 ; index<width ; ++index) {
        newboard[index] = (char*)calloc(height, sizeof(char));
    }
	
    printf("Arrancamo");
	for (int column=0; column<width; column++) {
        for (int row=0; row<height; row++) {
            a = vecinos(*board, column, row,height,width);
            if (board[column][row] && (a == 2 || a == 3)) newboard[column][row] = 1;
            if (!board[column][row] && a == 3) newboard[column][row] = 1;
            if (a < 2 && a > 3) newboard[column][row] = 0;
    	}	
    }

	
	for (int row=0; row<height; row++) {
        for (int column=0; column<width; column++) {
	    	board[row][column] = newboard[row][column];
	    }
    }


    for (int index=0 ; index<width ; ++index) {
        free(newboard[index]);
    }
    free(newboard);
}

/* print the life board */

void print (int width, int height, char** board) {
	
	for (int column=0; column<width; column++) {

		/* print each column position... */

		for (int row=0; row<height; row++) {
			printf ("%c", board[row][column] ? 'x' : '.');
		}

		/* followed by a carriage return */

		printf ("\n");
	}
}

/* read a file into the life board */

void read_file (int width,int height,char** board, char *name) {
	FILE	*f;
	int	row, column;
	char line[100];

	f = fopen (name, "r");
	
    while(fgets(line, 100, f)){
        char * pch;
        pch = strtok (line," ");
        int coord[2];
        int counter = 0;
        while (pch != NULL) {
            if (counter == 3) {
                printf("Error");
            }
            coord[counter] = atoi(pch);
            pch = strtok (NULL, " \n");
            counter ++;
        }

		board[coord[1]][coord[0]] = 1;

	}

	fclose (f);
}

/* main program */

int main (int argc, char *argv[]) {
	
    int repet = atoi(argv[1]);
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    
    char** board = (char**)calloc(width, sizeof(char*));

    for (int index=0 ; index<width ; ++index) {
        board[index] = (char*)calloc(height, sizeof(char));
    }

	read_file (width,height,board, argv[4]);


	for (int i=0; i<repet; i++) {
		print(width,height,board);
		// play (width,height,board);
		/* clear the screen using VT100 escape codes */
        printf("\n");
		// puts ("\033[H\033[J");
	}

}