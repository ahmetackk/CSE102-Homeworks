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

// This function controls a puzzle is containig the taken number
int control_create_puzzle(  Puzzle* puzzle,     // Boards pointer
                            int num             // Number which will control 
                            )
{
    // For size of puzzles
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if (num == puzzle->board[i][j]){
                return 1;
            }
        }
    }
    return 0;
}

// Print taken puzzle to terminal
void print_puzzle(  Puzzle* puzzle // Boards pointer
                    )
{    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if (puzzle->board[i][j] == 0)
            {
                printf("_ ");
            }
            else{
                printf("%d ", puzzle->board[i][j]);
            }
        }
        printf("\n");
    }
    
}

// Controls puzzle is solved
int control_win_statue( Puzzle* puzzle // Boards pointer
                        )
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if (i == 2 && j == 2) return 1;
            else if (puzzle->board[i][j] != ((i*3) + j + 1)) return 0;
        }
    }
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

// Creates an random puzzle and returns
Puzzle create_random_puzzle(){
    // For randomize
    srand(time(NULL));
    // Variables
    int randnum, filled = 0;
    Puzzle puzzle;
    
    // For size of puzzle
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            // Create a random number
            create_rand_num:
            randnum = rand() % 9;
            // If current puzzle containing created number then recreate another number
            if (control_create_puzzle(&puzzle, randnum) && filled < 9){
                goto create_rand_num;
            }
            else{
                // Else place it
                puzzle.board[i][j] = randnum;
                filled++;
            }
        }
    }

    // Create an empty file for board
    FILE* board;
    board = fopen("board.txt", "w+");

    if (board == NULL)
    {
        printf("File cannot opened!\n");
    }

    // Print puzzle to file
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if (puzzle.board[i][j] == 0)
            {
                fprintf(board, "_ ");
            }
            else{
                fprintf(board, "%d ", puzzle.board[i][j]);
            }
        }
        fprintf(board, "\n");
    }
    fprintf(board, "\n");
    fclose(board);
    // Return puzzle
    return puzzle;
}

// This function makes taken moves to puzzle if move is legal
void make_move( Puzzle* puzzle,         // Boards pointer
                int move_number,        // The number which will move
                char move_direction     // Direction of move
                )
{
    // Variables
    int x, y, tempnum = -1;
    // Find the number which will move
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if (puzzle->board[i][j] == move_number)
            {
                x = j;
                y = i;     
            }
        }
    }

    // Open board file
    FILE* board;
    board = fopen("board.txt", "a");

        if (board == NULL)
    {
        printf("File cannot opened!\n");
    }

    // Move switch
    switch (move_direction)
    {
    case 'U':
        // If move is illegal make a warning
        if ((y - 1) < 0){
            printf("%d-%c is an illegal move! Make a legal move!\n", move_number, move_direction);  
            while(getchar() == ' ');
            getchar();
        }
        // Else make the move
        else{
            fprintf(board, "User move: %d-U\n", move_number);
            printf("User move: %d-U\n", move_number);
            tempnum = puzzle->board[y - 1][x];
            puzzle->board[y - 1][x] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;
        }
        break;
    case 'D':
        if ((y + 1) > 2){
            printf("%d-%c is an illegal move! Make a legal move!\n", move_number, move_direction);  
            while(getchar() == ' ');
            getchar();
        }
        else{
            fprintf(board, "User move: %d-D\n", move_number);
            printf("User move: %d-D\n", move_number);
            tempnum = puzzle->board[y + 1][x];
            puzzle->board[y + 1][x] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;
        }
        break;
    case 'R':
        if ((x + 1) > 2){
            printf("%d-%c is an illegal move! Make a legal move!\n", move_number, move_direction);  
            while(getchar() == ' ');
            getchar();
        }
        else{
            fprintf(board, "User move: %d-R\n", move_number);
            printf("User move: %d-R\n", move_number);
            tempnum = puzzle->board[y][x + 1];
            puzzle->board[y][x + 1] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;
        }
        break;
    case 'L':
        if ((x - 1) < 0){
            printf("%d-%c is an illegal move! Make a legal move!\n", move_number, move_direction);  
            while(getchar() == ' ');
            getchar();
        }
        else{
            fprintf(board, "User move: %d-L\n", move_number);
            printf("User move: %d-L\n", move_number);
            tempnum = puzzle->board[y][x - 1];
            puzzle->board[y][x - 1] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;
        }
        break;
    default:
        break;
    }

    // If move is done print to board file
    if (tempnum != -1)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {   
                if (puzzle->board[i][j] == 0)
                {
                    fprintf(board, "_ ");
                }
                else{
                    fprintf(board, "%d ", puzzle->board[i][j]);
                }
            }
            fprintf(board, "\n");
        }
        fprintf(board, "\n");
        fclose(board);
    }
}

// Fastest version of auto_finish to not take a segmantation fault
int pc_finish(  Puzzle* puzzle,     // Boards pointer
                int number,         // Target number to take it to right place in the board
                int number_of_move  // Number of total moves  
                )
{
    // Variables
    int x, y, target_x, target_y ,tempnum;
    // Open file
    FILE* board;
    board = fopen("board.txt", "a");

    if (board == NULL)
    {
        printf("File cannot opened!\n");
    }

    // Find target numbers right location
    if ((number % 3) == 0) target_x = 2;
    else target_x = ((number % 3) - 1);
    target_y = (int)((number - 1) / 3);

    // Find target numbers current location
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){   
            if (puzzle->board[i][j] == number)
            {
                x = j;
                y = i;
            }
        }
    }

    // If number is in right location
    if (x == target_x && y == target_y)
    {   
        number++;
    }
    // Else
    else
    {   
        // If current x location is true then make move up or down
        if (x == target_x)
        {
            if (y < target_y)
            {   
                fprintf(board, "Computer move: %d-D\n", number);
                printf("Computer move: %d-D", number);
                // Take down
                tempnum = puzzle->board[y + 1][x];
                puzzle->board[y + 1][x] = puzzle->board[y][x];
                puzzle->board[y][x] = tempnum;
                y++;
            }
            else if (y > target_y)
            {   
                fprintf(board,"Computer move: %d-U\n", number);
                printf("Computer move: %d-U", number);
                // Take up
                tempnum = puzzle->board[y - 1][x];
                puzzle->board[y - 1][x] = puzzle->board[y][x];
                puzzle->board[y][x] = tempnum;
                y--;
            }
                
        }
        // Else firstly take number to right x location
        else
        {
            if (x > target_x)
            {   
                fprintf(board,"Computer move: %d-L\n", number);
                printf("Computer move: %d-L", number);
                // Take left
                tempnum = puzzle->board[y][x - 1];
                puzzle->board[y][x - 1] = puzzle->board[y][x];
                puzzle->board[y][x] = tempnum;
                x--;
            }
            else if (x < target_x)
            {   
                fprintf(board,"Computer move: %d-R\n", number);
                printf("Computer move: %d-R", number);
                // Take right
                tempnum = puzzle->board[y][x + 1];
                puzzle->board[y][x + 1] = puzzle->board[y][x];
                puzzle->board[y][x] = tempnum;
                x++;
            }
        }

        // After move if numbers is in the right place keep going with other number
        if (x == target_x && y == target_y)
        {   
            number++;
        }
        number_of_move++;

        // Print board to file
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {   
                if (puzzle->board[i][j] == 0)
                {
                    fprintf(board, "_ ");
                }
                else{
                    fprintf(board, "%d ", puzzle->board[i][j]);
                }
            }
            fprintf(board, "\n");
        }
        fprintf(board, "\n");
        fclose(board);
        
        // Print board to terminal
        printf("\n");
        print_puzzle(puzzle);
        printf("\n");
    }

    // If next number is smaller than 9 recursive
    if (number < 9)
    {   
        return pc_finish(puzzle, number, number_of_move);
    }
    // If next number is 9 that means board is solved then return number of moves 
    else
    {   
        return number_of_move;
    }

}

// Finishes board with random moves
int auto_finish(    Puzzle* puzzle,         // Boards pointer
                    int number_of_move      // Number of total moves
                    )
{
    // Variables
    int number, tempnum, move, x, y;
    // Open file
    FILE* board;
    board = fopen("board.txt", "a");

    if (board == NULL)
    {
        printf("File cannot opened!\n");
    }

    // Create random number
    number = rand() % 8 + 1;
    // Find created numbers location
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){   
            if (puzzle->board[i][j] == number)
            {
                x = j;
                y = i;
            }
        }
    }
    // Create random move
    random_move:
    move = rand() % 4 + 1;
    // Move switch
    switch (move)
    {
    case 1:
        // Control move is legal
        if ((y - 1) < 0){
            // If move is not illegal create another random move
            goto random_move;
        }
        // If move is legal do
        else{
            // Print terminal and file
            fprintf(board, "Computer move: %d-U\n", number);
            printf("Computer move: %d-U", number);
            // UP
            tempnum = puzzle->board[y - 1][x];
            puzzle->board[y - 1][x] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;

            number_of_move++;
        }
        break;
    case 2:
        if ((y + 1) > 2){
            goto random_move;
        }
        else{
            // DOWN
            fprintf(board, "Computer move: %d-D\n", number);
            printf("Computer move: %d-D", number);

            tempnum = puzzle->board[y + 1][x];
            puzzle->board[y + 1][x] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;

            number_of_move++;
        }
        break;
    case 3:
        if ((x + 1) > 2){
           goto random_move;
        }
        else{
            fprintf(board, "Computer move: %d-R\n", number);
            printf("Computer move: %d-R", number);
            // RIGHT
            tempnum = puzzle->board[y][x + 1];
            puzzle->board[y][x + 1] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;

            number_of_move++;
        }
        break;
    case 4:
        if ((x - 1) < 0){
            goto random_move;
        }
        else{
            fprintf(board, "Computer move: %d-L\n", number);
            printf("Computer move: %d-L", number);
            // LEFT
            tempnum = puzzle->board[y][x - 1];
            puzzle->board[y][x - 1] = puzzle->board[y][x];
            puzzle->board[y][x] = tempnum;

            number_of_move++;
        }
        break;
    default:
        break;
    }

    // Print board to file
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
            if (puzzle->board[i][j] == 0)
            {
                fprintf(board, "_ ");
            }
            else{
                fprintf(board, "%d ", puzzle->board[i][j]);
            }
        }
        fprintf(board, "\n");
    }
    fprintf(board, "\n");
    fclose(board);

    // Print board to terminal
    printf("\n");
    print_puzzle(puzzle);
    printf("\n");
    
    // If puzzle is solved return number of moves
    if (control_win_statue(puzzle))
    {
        return number_of_move;
    }
    // Else recursive
    else
    {
        return auto_finish(puzzle, number_of_move);
    }

}