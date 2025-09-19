#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/* Direction defines */
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

// Clear terminal
void reset_terminal(){
    printf("\033[2J");  
    printf("\033[0;0f");
}

// Draw line with '-'
void draw_line(int a){
    for (int i = 0; i < a; i++){
        printf("-");
    }
}

// Control function for if door and character are in same place
int control_stat(int d_y, int d_x, int c_y, int c_x){
    if (d_y == c_y)
    {
        if (c_x == d_x)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

// Draw room function for game 
void draw_room(int size, int d_y, int d_x, int c_y, int c_x){
    
    // Draw line top 
    draw_line((2 * size) + 1);
    printf("\n");

    // With 2 for loops draw rooms in order
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {   
            // If taken doors location is overlap with to be drawn rooms location draw D
            if (j == d_x && i == d_y)
            {   
                printf("|D");
            }
            // If taken characters locations is overlap with to be drawn rooms location draw C
            else if (j == c_x && i == c_y)
            {
                printf("|C");
            }
            else
            {
                printf("| ");
            }  
        }    
        printf("|\n");
    }

    // Draw line bottom
    draw_line((2 * size) + 1);
    printf("\n");
}

void game(int size, int d_y, int d_x, int c_y, int c_x, int step_counter){

    // If door and chracter is overlap already finish the game
    if(control_stat(d_y, d_x, c_y, c_x) == 1)
    {
        reset_terminal();
        printf("CONGRULATIONS!\n");
        // Print number of moves
        printf("Number of moves: %d\n", step_counter);
        while (getchar() != '\n');
        getchar();
    }
    else
    {   
        // Reset terminal and draw room
        reset_terminal();
        draw_room(size, d_y, d_x, c_y, c_x);
        take_key:
        while (getchar() != '\n');

        // Take direction key from user
        switch (getchar())
        {
        /* Take directions and update locations of character */
        case UP:
            c_y--;
            // If character is hit to the wall
            if (c_y < 1)
            {
                printf("Character hit to the wall!\n");
                c_y++;
                goto take_key;
            }
            break;
        case DOWN:
            c_y++;
            // If character is hit to the wall
            if (c_y > size)
            {
                printf("Character hit to the wall!\n");
                c_y--;
                goto take_key;
            }
            break;
        case LEFT:
            c_x--;
            // If character is hit to the wall
            if (c_x < 1)
            {
                printf("Character hit to the wall!\n");
                c_x++;
                goto take_key;
            }
            break;
        case RIGHT:
            c_x++;
            // If character is hit to the wall
            if (c_x > size)
            {
                printf("Character hit to the wall!\n");
                c_x--;
                goto take_key;
            }
            break;
        default:
            goto take_key;
            break;
        }
        // After move increase moves of number
        step_counter++;
        // Recall game until game is finished
        game(size, d_y, d_x, c_y, c_x, step_counter);
    }
    
    
}
