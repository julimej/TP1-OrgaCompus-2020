#include <stdint.h>
#include "cellsgrid.h"

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
