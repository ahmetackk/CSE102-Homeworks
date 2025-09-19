#include <stdio.h>
#include <time.h>
#include "util.h"

/*----- MAIN ------*/

int main(){
    /* Variables */
    int choice, size, d_y, d_x, c_y, c_x, stepcounter;
    stepcounter = 0;

    /* Menu write */
    menu_start:
    reset_terminal();
    printf("Welcome to 2D puzzle game!\n");
    printf("1. New Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");

    scanf("%d", &choice);

    /* Menu choice states with switch case */
    switch (choice)
    {
    case 1:
        /* Enter game */
        // Take rooms square edge size
        printf("Please enter rooms square edge size(between 5 - 10): ");
        enter_size:
        scanf("%d", &size);
        // If size is lower than 5 or bigger than 10 give error and take again
        if(size < 5 || size > 10)
        {
            printf("Please enter between 5 - 10!\n");
            goto enter_size;
        }
        // Randomize doors and characters location
        srand(time(0));
        d_x = ((rand() % size) + 1);
        d_y = ((rand() % size) + 1);
        c_x = ((rand() % size) + 1);
        c_y = ((rand() % size) + 1);
        // I didnt add check if the locations are same on purpose becase of if you are lucky enough you won already
        // Game start
        game(size, d_y, d_x, c_y, c_x, stepcounter);
        goto menu_start;
        break;
    case 2:
        /* Help choice */
        reset_terminal();
        printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n");
        printf("The character can not attempts to move through a wall.\n");
        printf("Game will be end when the character reaches to the door.\n");
        // Wait until take any input
        while (getchar() != '\n');
        getchar();
        goto menu_start;
        break;
    default:
        // Exit from program
        reset_terminal();
        printf("GOODBYE!\n");
        return 0;
        break;
    }

}