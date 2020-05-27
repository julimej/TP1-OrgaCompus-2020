#ifndef __CELLS_GRID_H__
#define __CELLS_GRID_H__

#include "cell.h"
#include <stdlib.h>

#define CELL_AT(x,y,r,c) ((x) * (r) + (y))

typedef struct {
    uint32_t rows,columns;
    char *grid;
} cells_grid_t;

cells_grid_t* make_grid(unsigned int height,unsigned int width);

char get_cell_at(cells_grid_t* self, uint32_t row, uint32_t column);

void set_cell_alive(cells_grid_t* self,uint32_t row, uint32_t column);

void set_cell_dead(cells_grid_t* self,uint32_t row, uint32_t column);

void destroy_grid(cells_grid_t* grid);

#endif /* __CELLS_GRID_H__ */
