#include <stdio.h>
#include "util.h"

/*----- MAIN ------*/

int main(){
    reset_terminal();
    // Create board
    Block*** board = init_board();
    // Play 
    play(board);
    // Free board
    free(board);
}