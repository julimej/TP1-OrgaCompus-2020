#include "cellsgrid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(int width,int height,cells_grid_t* board, const char *name) {
	FILE *f;
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

        // printf("Row: %d Column: %d", coord[1],coord[0]);
		set_cell_alive(board,coord[1],coord[0]);

	}

	fclose (f);
}

void print (cells_grid_t* board, char* prefix, int iter) {
    FILE* f;

    char filename[160];
    snprintf(filename, sizeof filename, "%s_%d", prefix, iter);

    f = fopen(filename,"w");

    if (f == NULL) {
        fprintf(stderr,"Error al crear el archivo de salida");
        return;
    }
    
	for (int column=0; column<board->columns; column++) {

		/* print each column position... */

		for (int row=0; row<board->rows; row++) {
			fprintf(f,"%c", get_cell_at(board,row,column) ? 'x' : '.');
		}

		/* followed by a carriage return */
        fprintf(f,"\n");
	}

    fclose(f);
}
