CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= tp1_asm

all: tp1_cells

tp1_cells: cellsgrid.h cellsgrid.c game_of_life.c
	gcc -g $^ -o $@

tpi_cells_asm: cellsgrid.h cellsgrid game_of_life.c

clean:
	rm tp1_*
