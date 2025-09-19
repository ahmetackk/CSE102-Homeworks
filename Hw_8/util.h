#ifndef _UTIL_H_
#define _UTIL_H_

// Puzzle struct
typedef struct{
    int board[3][3];
} Puzzle;

void reset_terminal();

int control_create_puzzle(Puzzle* puzzle, int num);

void print_puzzle(Puzzle* puzzle);

int control_win_statue(Puzzle* puzzle);

Puzzle create_random_puzzle();

void make_move(Puzzle* puzzle, int move_number, char move_direction);

int pc_finish(Puzzle* puzzle, int target_number, int number_of_move);

int auto_finish(Puzzle* puzzle, int number_of_move);

#endif /* _UTIL_H_ */