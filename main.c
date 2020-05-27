//
// Created by julian on 5/25/20.
//

#include "cellsgrid.h"
#include "filereader.c"


int vecinos(unsigned char* board, unsigned int i, unsigned int j, unsigned int rows, unsigned int columns) {
	int	count = 0;

	for (int k=-1; k<=1; k++) {
        for (int l=-1; l<=1; l++) {
            int32_t row = (i+k +rows) % rows;
            int32_t column = (j+l+columns) % columns;
            if (k || l) {
                if (board[CELL_AT(row,column,rows,columns)]) count++;
            }
        }
    }
	return count;
}

void play (cells_grid_t* board) {

	int	a;

    cells_grid_t* newboard = make_grid(board->rows,board->columns);
	
	for (int column=0; column<board->columns; column++) {
        for (int row=0; row<board->rows; row++) {
            a = vecinos(board->grid, row, column,board->rows,board->columns);
            if (get_cell_at(board,row,column) && (a == 2 || a == 3)) set_cell_alive(newboard,row,column);
            if (!get_cell_at(board,row,column) && a == 3) set_cell_alive(newboard,row,column);
            if (a < 2 && a > 3) set_cell_dead(newboard,row,column);
    	}	
    }

	
	for (int row=0; row<board->rows; row++) {
        for (int column=0; column<board->columns; column++) {
	    	if (get_cell_at(newboard,row,column)) {
                set_cell_alive(board,row,column);
            } else {
                set_cell_dead(board,row,column);
            }
	    }
    }

    destroy_grid(newboard);
}

int main(int argc, char const *argv[]) {
    int repet = atoi(argv[1]);
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    cells_grid_t *grid = make_grid(height,width);
    read_file(width,height,grid,argv[4]);
    
    for (int i=0; i<repet; i++) {
        // printf("State %d\n", i);
		print(grid);
		play(grid);
	}

    destroy_grid(grid);
    return 0;
}
