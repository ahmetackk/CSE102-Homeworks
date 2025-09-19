#ifndef _UTIL_H_
#define _UTIL_H_

// Point struct
typedef struct {
    int row;
    int col;
} Point;

// Block struct
typedef struct {
    char type;
    int value;
} Block;

void reset_terminal();

void move(Point** snake, char movechar);

int check_status(Block*** board, Point** snake);

Point** update(Block*** board, Point** snake, char movechar, int movenumber);

Block*** init_board();

void draw_board(Block*** board, Point** snake);

void play(Block*** board);

#endif /* _UTIL_H_ */