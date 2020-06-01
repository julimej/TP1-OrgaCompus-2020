#ifndef __UTILS_H__
#define __UTILS_H__

#include "cellsgrid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(int width,int height,cells_grid_t* board, const char *name) ;

void save_state(cells_grid_t* board, const char* prefix, int iter) ;


#endif /* __CELLS_GRID_H__ */

