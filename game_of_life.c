#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h>

#include "cellsgrid.h"
#include "utils.c"

int vecinos(unsigned char* board, unsigned int i, unsigned int j, unsigned int rows, unsigned int columns);

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

// void play (cells_grid_t* board) {

// 	int	a;

//     unsigned int rows = board->rows;
//     unsigned int columns = board->columns;

//     cells_grid_t* aux_grid = make_grid(rows,columns);
	
// 	for (int column=0; column<columns; column++) {
//         for (int row=0; row<rows; row++) {
//             a = vecinos(board->grid, row, column,rows,columns);
//             if (get_cell_at(board,row,column) && (a == 2 || a == 3)) set_cell_alive(aux_grid,row,column);
//             if (!get_cell_at(board,row,column) && a == 3) set_cell_alive(aux_grid,row,column);
//             if (a < 2 && a > 3) set_cell_dead(aux_grid,row,column);
//     	}	
//     }

	
// 	for (int row=0; row<rows; row++) {
//         for (int column=0; column<columns; column++) {
// 	    	if (get_cell_at(aux_grid,row,column)) {
//                 set_cell_alive(board,row,column);
//             } else {
//                 set_cell_dead(board,row,column);
//             }
// 	    }
//     }

//     destroy_grid(aux_grid);
//}

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
    

	int	a;

    unsigned int rows = grid->rows;
    unsigned int columns = grid->columns;

    cells_grid_t* aux_grid = make_grid(rows,columns);
	


    for (int i=0; i<iterations; i++) {
		
        save_state(grid,prefix,i);

		for (int column=0; column<columns; column++) {
            for (int row=0; row<rows; row++) {
                a = vecinos(grid->grid, row, column,rows,columns);
                if (get_cell_at(grid,row,column) && (a == 2 || a == 3)) set_cell_alive(aux_grid,row,column);
                if (!get_cell_at(grid,row,column) && a == 3) set_cell_alive(aux_grid,row,column);
                if (a < 2 && a > 3) set_cell_dead(aux_grid,row,column);
            }	
        }

        
        for (int row=0; row<rows; row++) {
            for (int column=0; column<columns; column++) {
                if (get_cell_at(aux_grid,row,column)) {
                    set_cell_alive(grid,row,column);
                } else {
                    set_cell_dead(grid,row,column);
                }
                set_cell_dead(aux_grid,row,column);
            }
        }

	}

    destroy_grid(aux_grid);
    destroy_grid(grid);

    printf("Listo\n");

    return 0;
}
