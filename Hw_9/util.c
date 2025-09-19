#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "util.h"

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

// Reset terminal for clean image
void reset_terminal(){
    printf("\033[2J");
    printf("\033[0;0f");
}

void move(Point** snake,        // Snake  
            char movechar)      // Move direction
{     
    // Find snake length
    int snake_length = 0;
    while (snake[snake_length]->row != -1 && snake[snake_length]->col != -1) snake_length++;

    // Move snakes head according to the direction of movement
    switch (movechar)
    {
    case 'w':
        if (snake_length != 1)
        {
            if ((snake[1]->row + 1) != snake[0]->row)
            {
                snake[0]->row--;
            }
        }
        else snake[0]->row--;
        break;
    case 's':
        if (snake_length != 1)
        {
            if ((snake[1]->row - 1) != snake[0]->row)
            {
                snake[0]->row++;
            }
        }
        else snake[0]->row++;
        break;
    case 'a':
        if (snake_length != 1)
        {
            if ((snake[1]->col + 1) != snake[0]->col)
            {
                snake[0]->col--;
            }
        }
        else snake[0]->col--;
        break;
    case 'd':
        if (snake_length != 1)
        {
            if ((snake[1]->col - 1) != snake[0]->col)
            {
                snake[0]->col++;
            }
        }
        else snake[0]->col++;
        break;
    default:
        break;
    }
}

int check_status(Block*** board,        // Board 
                    Point** snake)      // Snake
{
    // Find snake length
    int snake_length = 0;
    while (snake[snake_length]->row != -1 && snake[snake_length]->col != -1) snake_length++;
    
    // Control does the head of the snake hit its own body if its return 1
    for (int i = 1; i < snake_length; i++)
    {
        if (snake[0]->row == snake[i]->row && snake[0]->col == snake[i]->col) return 1;
    }
    
    // Control does the snake collide with the wall if its return 1
    if (snake[0]->row == 0 || snake[0]->row == 11) return 1;
    if (snake[0]->col == 0 || snake[0]->col == 11) return 1;
    
    // Control does the snake encounter an obstacle that has x number of blocks, where x is greater than the length of the snake 
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (board[i][j]->type == 'o')
            {   
                if (snake[0]->row == i && snake[0]->col == j)
                {
                    if (board[i][j]->value > snake_length) return 1;
                }
            }
        }
    }

    // If any condition is not met return 0
    return 0;
}

Point** update(Block*** board,          // Board
                Point** snake,          // Snake
                char movechar,          // Move direction
                int movenumber)         // Number of total moves
{
    // Find snake length
    int snake_length = 0, obstacle_number = 0;
    while (snake[snake_length]->row != -1 && snake[snake_length]->col != -1) snake_length++;

    // Find obstacles number on board
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){   
            if (board[i][j]->type == 'o') obstacle_number++;
        }
    }

    // Take snakes heads board location
    int snake_old_head_row = snake[0]->row;
    int snake_old_head_col = snake[0]->col;

    // Make move
    move(snake, movechar);

    // After the move if snakes head is met with bait
    if (board[snake[0]->row][snake[0]->col]->type == 'b')
    {   
        // Increase snake length
        snake_length++;
        // Realloc snake array 
        snake = (Point*)realloc(snake, (snake_length+1)*sizeof(Point*));
        snake[snake_length] = (Point*)malloc(sizeof(Point));

        // Move the remaining part of the snake
        for (int i = snake_length; i > 1; i--)
        {   
            snake[i]->row = snake[i - 1]->row;
            snake[i]->col = snake[i - 1]->col;
        }
        snake[1]->row = snake_old_head_row;
        snake[1]->col = snake_old_head_col;

        // Create new bait
        int bait_row, bait_col, new_bait_row, new_bait_col;

        // Find old bait location
        for (int i = 0; i < 12; i++){
            for (int j = 0; j < 12; j++){   
                if (board[i][j]->type == 'b')
                {   
                    bait_row = i;
                    bait_col = j;
                }
            }
        }

        // Random bait location
        bait_random:
        new_bait_row = rand() % 10 + 1;
        new_bait_col = rand() % 10 + 1;

        // If created random location is not empty then re-random
        for (int i = 0; i < snake_length; i++)
        {
            if (snake[i]->row == new_bait_row && snake[i]->col == new_bait_col) goto bait_random;
        }
        if (board[new_bait_row][new_bait_col]->type == 'b' || board[new_bait_row][new_bait_col]->type == 'o') goto bait_random;

        // Update board with new bait
        board[new_bait_row][new_bait_col]->type = 'b';
        board[new_bait_row][new_bait_col]->value = 0;
        board[bait_row][bait_col]->type = 'e';
        board[bait_row][bait_col]->value = 0;

    }
    // If snakes head is met with obstacle
    else if (board[snake[0]->row][snake[0]->col]->type == 'o')
    {   
        // If snakes length is bigger than obstacles value clear obstacle
        if (snake_length > board[snake[0]->row][snake[0]->col]->value)
        {
            board[snake[0]->row][snake[0]->col]->type = 'e';
            board[snake[0]->row][snake[0]->col]->value = 0;
            obstacle_number--;
        }
        // Move the remaining part of the snake
        for (int i = snake_length - 1; i > 1; i--)
        {   
            snake[i]->row = snake[i - 1]->row;
            snake[i]->col = snake[i - 1]->col;
        }
        if (snake_length != 1)
        {
            snake[1]->row = snake_old_head_row;
            snake[1]->col = snake_old_head_col;
        }
    }
    // If snakes head is not met with anything
    else
    {   
        for (int i = snake_length - 1; i > 1; i--)
        {   
            snake[i]->row = snake[i - 1]->row;
            snake[i]->col = snake[i - 1]->col;
        }
        if (snake_length != 1)
        {
            snake[1]->row = snake_old_head_row;
            snake[1]->col = snake_old_head_col;
        }
    }

    // One in 5 moves
    if (movenumber % 5 == 0)
    {   
        int new_obs_row, new_obs_col, new_obs;
        // Update obstacles
        obstacle_random:
        new_obs = rand() % 15 + 1;
        new_obs_row = rand() % 10 + 1;
        new_obs_col = rand() % 10 + 1;

        for (int i = 0; i < snake_length; i++)
        {
            if (snake[i]->row == new_obs_row && snake[i]->col == new_obs_col) goto obstacle_random;
        }
        if (board[new_obs_row][new_obs_col]->type == 'b') goto obstacle_random;

        // If obstacle number is not more than 3 create new random obstacle
        if (obstacle_number < 3)
        {
            if (board[new_obs_row][new_obs_col]->type == 'o') board[new_obs_row][new_obs_col]->value += new_obs;
            else{
                board[new_obs_row][new_obs_col]->type = 'o';
                board[new_obs_row][new_obs_col]->value = new_obs;
            }
        }
        // If obstacle number is 3 then clear old obstacles
        else
        {
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){   
                    if (board[i][j]->type == 'o'){
                        board[i][j]->type = 'e';
                        board[i][j]->value = 0;
                    }
                }
            }
            board[new_obs_row][new_obs_col]->type = 'o';
            board[new_obs_row][new_obs_col]->value = new_obs;
        }
    }
    // Return reallocated snake 
    return snake;
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

Block*** init_board(){
    int bait_row, bait_col, obstacle_row, obstacle_col;
    // Create random locations for bait and obstacle
    random: 
    bait_row = rand() % 10 + 1;
    bait_col = rand() % 10 + 1;
    obstacle_row = rand() % 10 + 1;
    obstacle_col = rand() % 10 + 1;
    // If obstacle and bait is in same location re-random
    if (obstacle_col == bait_col && obstacle_row == bait_row) goto random;
    if (obstacle_col == 1 && obstacle_row == 1) goto random;
    if (bait_col == 1 && bait_row == 1) goto random;

    // Malloc board
    Block*** board = (Block***)malloc(12 * sizeof(Block**));

    // Malloc every line and find random locations to update board according to the bait and obstacle
    for (int i = 0; i < 12; i++){
        board[i] = (Block**)malloc(12 * sizeof(Block*));
        for (int j = 0; j < 12; j++){
            board[i][j] = (Block*)malloc(sizeof(Block));
            
            if (j == bait_col)
            {   
                if (i == bait_row)
                {   
                    board[i][j]->type = 'b';
                    board[i][j]->value = 0;
                }
            }
            else if (j == obstacle_col)
            {   
                if (i == obstacle_row)
                {   
                    board[i][j]->type = 'o';
                    board[i][j]->value = rand() % 9 + 1;
                }
            }
            else
            {
                board[i][j]->type = 'e';
                board[i][j]->value = 0;
            }
        }
    }
    // Return board
    return board;
}

void draw_board(Block*** board,     // Board
                Point** snake)      // Snake
{

    int k = 0, flag = 1;
    printf("\n -------------------- \n");
    for (int i = 1; i < 11; i++){
        printf("| ");
        for (int j = 1; j < 11; j++){
            while (snake[k]->row != -1 && snake[k]->col != -1)
            {   
                // If we meet with snakes part
                if (snake[k]->row == i && snake[k]->col == j)
                {   
                    // If meet snakes head print "O"
                    if (k == 0) printf("O ");
                    // If meet snakes any part print "X"
                    else printf("X ");
                    flag = 0;
                }
                k++;
            }
            // If we didnt meet with snakes part
            if (flag)
            {   
                // If we meet with bait
                if (board[i][j]->type == 'b')
                {
                    printf(". ");
                }
                // If we meet with obstacle
                else if (board[i][j]->type == 'o')
                {   
                    if ((board[i][j]->value / 10) >= 1) printf("%d", board[i][j]->value);
                    else printf("%d ", board[i][j]->value);
                }
                // If we didnt meet anything
                else
                {
                    printf("  ");
                }
            }
            
            flag = 1;
            k = 0;
        }
        printf("|\n");
    }
    printf(" -------------------- ");

}

void play(Block*** board)   // Board
{
    // Create snake in top-left of board
    srand(time(NULL));
    Point** snake = (Point*)malloc(2*sizeof(Point));
    snake[0] = (Point*)malloc(sizeof(Point));
    snake[1] = (Point*)malloc(sizeof(Point));
    snake[0]->row = 1;
    snake[0]->col = 1;
    snake[1]->row = -1;
    snake[1]->col = -1;

    int movenumber = 0;
    char movechar;
    // While game is not end
    while (check_status(board, snake) == 0)
    {   
        // Reset terminal and draw board
        reset_terminal();
        draw_board(board, snake);
        // Take move
        printf("\nPlease enter move: ");
        scanf(" %c", &movechar);
        // Update game
        snake = update(board, snake, movechar, movenumber);
        // Increase move number
        movenumber++;
    }
    // Free snake
    free(snake);
}