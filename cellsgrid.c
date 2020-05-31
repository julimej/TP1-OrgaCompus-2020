//
// Created by julian on 5/25/20.
//

#include "cellsgrid.h"

cells_grid_t* make_grid(unsigned int height,unsigned int width) {
    cells_grid_t* grid;

    grid = malloc(sizeof(cells_grid_t));

    grid->grid = (char*) calloc(height * width,sizeof(char));
    grid->columns = width;
    grid->rows = height;
    
    return grid;
}


char get_cell_at(cells_grid_t* self, unsigned int row, unsigned int column) {
    return self->grid[CELL_AT(row,column,self->rows,self->columns)];
}

void set_cell_alive(cells_grid_t* self,unsigned int row, unsigned int column) {
    self->grid[CELL_AT(row,column,self->rows,self->columns)] = 1;
}

void set_cell_dead(cells_grid_t* self,unsigned int row, unsigned int column) {
    self->grid[CELL_AT(row,column,self->rows,self->columns)] = 0;
}

void destroy_grid(cells_grid_t* grid) {
    free(grid->grid);
    free(grid);
}