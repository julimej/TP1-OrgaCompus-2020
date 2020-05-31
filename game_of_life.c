#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h>

#include "cellsgrid.h"
#include "filereader.c"

static void show_warn(const char *p) {
     fprintf(stderr, " %s\n", p);
}

void show_error_dim(char* medida) {
    fprintf(stderr,"El %s debe ser mayor a 0\n",medida);
}

static void show_help() {
    fprintf(stderr, " ./tpi_cells <iterations> <width> <height> <filename> -o <prefix>\n");
    fprintf(stderr, "  -h --help: Print this message and exit\n");
    fprintf(stderr, "  -v --version: Da la version del programa\n");
    fprintf(stderr, "  -o : Prefijo de los archivos\n");
}

static void show_version() {
  printf("v1.0.0\n");
}

int vecinos(unsigned char* board, unsigned int i, unsigned int j, unsigned int rows, unsigned int columns) {
	int	count = 0;

	for (int k=-1; k<=1; k++) {
        for (int l=-1; l<=1; l++) {
            int32_t row = (i+k +rows) % rows;
            int32_t column = (j+l +columns) % columns;
            if (k || l) {
                if (board[CELL_AT(row,column,rows,columns)]) count++;
            }
        }
    }
	return count;
}

void play (cells_grid_t* board) {

	int	a;

    unsigned int rows = board->rows;
    unsigned int columns = board->columns;

    cells_grid_t* newboard = make_grid(rows,columns);
	
	for (int column=0; column<columns; column++) {
        for (int row=0; row<rows; row++) {
            a = vecinos(board->grid, row, column,rows,columns);
            if (get_cell_at(board,row,column) && (a == 2 || a == 3)) set_cell_alive(newboard,row,column);
            if (!get_cell_at(board,row,column) && a == 3) set_cell_alive(newboard,row,column);
            if (a < 2 && a > 3) set_cell_dead(newboard,row,column);
    	}	
    }

	
	for (int row=0; row<rows; row++) {
        for (int column=0; column<columns; column++) {
	    	if (get_cell_at(newboard,row,column)) {
                set_cell_alive(board,row,column);
            } else {
                set_cell_dead(board,row,column);
            }
	    }
    }

    destroy_grid(newboard);
}

int main(int argc, char * const argv[]) {

    int opt, s, len = 0;

    unsigned int iterations, width = 0, height = 0;
    char* prefix; 
    char* filename; 

    while ((opt = getopt(argc, argv, "o:hv:")) != -1) {
        switch(opt) {
            case 'o': 
                if (argc == 7) {
                    if (atoi(argv[1]) <= 0) {
                        show_error_dim("iteraciones");
                        exit(2);
                    } else {
                        iterations = atoi(argv[1]);
                    }
                    if (atoi(argv[2]) <= 0) {
                        show_error_dim("width");
                        exit(2);
                    } else {
                        width = atoi(argv[2]);
                    }
                    
                    if (atoi(argv[3]) <= 0) {
                        show_error_dim("height");
                        exit(2);
                    } else {
                        height = atoi(argv[3]);
                    }

                    filename = argv[4];
                } else {
                    show_help();
                    exit(2);
                }
                if (strcmp(optarg, "-") != 0) {
                    prefix = optarg;
                }
                break;

            case 'h': /* help */
                show_help();
                exit(0);
                break;

            case 'v': /* version */
                show_version();
                exit(0);
                break;

            default:
                show_help();
                exit(2);
                break; 
        }
    }

    if (width == 0){
        if (argc == 5) {
            if (atoi(argv[1]) <= 0) {
                show_error_dim("iteraciones");
                exit(2);
            } else {
                iterations = atoi(argv[1]);
            }
            if (atoi(argv[2]) <= 0) {
                show_error_dim("width");
                exit(2);
            } else {
                width = atoi(argv[2]);
            }
            
            if (atoi(argv[3]) <= 0) {
                show_error_dim("height");
                exit(2);
            } else {
                height = atoi(argv[3]);
            }
            filename = argv[4];
            prefix = filename;
        } else {
            show_help(argv[0]);
            exit(2);
        }
    }

    cells_grid_t *grid = make_grid(height,width);

    int result = read_file(width,height,grid,filename);
    
    if (result != 0) {
        destroy_grid(grid);
        return 1;
    }
    
    for (int i=0; i<iterations; i++) {
		print(grid,prefix,i);
		play(grid);
	}

    destroy_grid(grid);

    return 0;
}
