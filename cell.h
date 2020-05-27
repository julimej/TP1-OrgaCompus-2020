#ifndef __CELL_H__
#define __CELL_H__

#include <unistd.h>
#include <stdint.h>

typedef struct {
    uint32_t x, y, state;
} cell_t;

#endif /* __CELL_H__ */
