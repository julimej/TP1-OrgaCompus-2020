#ifndef __CELLS_GRID_H__
#define __CELLS_GRID_H__

#include <stdlib.h>
#include <stdint.h>

#define CELL_AT(y,x,r,c) ((x) * (r) + (y))

typedef struct {
    unsigned int rows,columns;
    char *grid;
} cells_grid_t;

cells_grid_t* make_grid(unsigned int height,unsigned int width);

char get_cell_at(cells_grid_t* self, unsigned int row, unsigned int column);

void set_cell_alive(cells_grid_t* self,unsigned int row, unsigned int column);

void set_cell_dead(cells_grid_t* self,unsigned int row, unsigned int column);

void destroy_grid(cells_grid_t* grid);

#endif /* __CELLS_GRID_H__ */

