#include "cellsgrid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(int width,int height,cells_grid_t* board, const char *name) {
	FILE *f;
	int	row, column;
	char line[100];

	f = fopen (name, "r");
	
    printf("Leyendo estado inicial..\n");

    if (f == NULL) {
        fprintf(stderr,"Error al abrir el archivo: %s\n",name);
        return 1;
    }

    while(fgets(line, 100, f)){
        char * pch;
        pch = strtok (line," ");
        int coord[2];
        int counter = 0;
        while (pch != NULL) {
            if (counter == 3) {
                fprintf(stderr,"El archivo debe cumplir con el formato establecido. Una sola coordenada por linea\n");      
                fclose(f);
                return 1;
            }
            coord[counter] = atoi(pch);
            pch = strtok (NULL, " \n");
            counter ++;
        }

        if (coord[1] >= height || coord[1] < 0 || coord[0] >= width || coord[0] < 0) {
            fclose(f);
            fprintf(stderr,"Las coordenadas deben estar dentro del rectangulo de dimensiones %d x %d\n", width,height);
            return 1;
        }
        
		set_cell_alive(board,coord[1],coord[0]);

	}

	fclose (f);
    return 0;
}

void save_state(cells_grid_t* board, const char* prefix, int iter) {
    FILE* f;

    char filename[160];
    snprintf(filename, sizeof filename, "%s_%04d.%s", prefix, iter,"pbm");

    f = fopen(filename,"w");

    if (f == NULL) {
        fprintf(stderr,"Error al crear el archivo de salida %s\n", filename);
        return;
    }

    printf("Grabando %s\n",filename);    
    fprintf(f,"%s\n","P1");
    fprintf(f,"%d %d\n",board->columns*8,board->rows*8);
    for (int column=0; column<board->columns; column++) {
	    for (size_t j = 0; j < 8; j++) {

            for (int row=0; row<board->rows; row++) {
                for (size_t i = 0; i < 8; i++) {          
                    fprintf(f,"%c ", get_cell_at(board,row,column) ? '1' : '0');
                }
            }
            

            fprintf(f,"\n");
        }

    }

    fclose(f);
}
