#include <stdio.h>
#include "util.h"

/*----- MAIN ------*/
int main(){
    // Variables
    int op, fileopen = 0, best_score, numberofmove = 0, pc_move_number;
    Puzzle newpuzzle;

    // Open best score file to take current best score
    FILE *scorefile;
    scorefile = fopen("best_score.txt", "r");

    if (scorefile == NULL)
    {
        printf("File cannot opened!\n");
    }

    fscanf(scorefile, "%d", &best_score);
    fclose(scorefile);

    // Print menu
    menu:
    reset_terminal();
    printf("Welcome to the 8-Puzzle Game!\n");
    printf("Please select an option:\n");
    printf("1. Play game as a user\n2. Finish the game with PC\n3. Finish the game with random moves\n4. Show the best score\n5. Exit\n> ");
    scanf("%d", &op);

    // Operation swicth
    switch (op)
    {
    case 1:
        // Create new random puzzle 
        newpuzzle = create_random_puzzle();
        int move_number;
        char move_direction;

        // Take move from user
        move:
        reset_terminal();
        print_puzzle(&newpuzzle);
        printf("\nEnter your move (number-direction, e.g., 2-R) : ");
        scanf("%d-%c", &move_number, &move_direction);

        // Control is move legal
        if (move_number > 8 || move_number < 1)
        {
            printf("\nPlease enter a number from board!\n");
            while(getchar() == ' ');
            getchar();
            goto move;
        }
        if (!(move_direction == 'L' || move_direction == 'R' || move_direction == 'U' || move_direction == 'D'))
        {
            printf("\nPlease enter a valid direction!\n");
            while(getchar() == ' ');
            getchar();
            goto move;
        }   

        // Make move
        make_move(&newpuzzle, move_number, move_direction);        

        // Control win statue
        if (control_win_statue(&newpuzzle))
        {   
            // If board is solved then take score and compare with current
            reset_terminal();
            print_puzzle(&newpuzzle);

            int new_score = (1000 - (10 * numberofmove));
            printf("\nCongratulations!\nYou finished the game.\n");
            printf("Total number of moves: %d\nYour score: %d\n", numberofmove, new_score);
            
            if (new_score > best_score)
            {
                scorefile = fopen("best_score.txt", "w+");

                if (scorefile == NULL)
                {
                    printf("File cannot opened!\n");
                }

                fprintf(scorefile, "%d", new_score);

                fclose(scorefile);
            }
        }
        else{
            // If board is not solved go back to make move
            numberofmove++;
            goto move;
        }
        // Wait until user press any key
        while(getchar() == ' ');
        getchar();
        goto menu;
    case 2:
        reset_terminal();
        // Create new random puzzle
        newpuzzle = create_random_puzzle();
        print_puzzle(&newpuzzle);
        printf("\n");
        // Finish with pc 
        pc_move_number = pc_finish(&newpuzzle, 1, 0);
        printf("\nComputer finished the game.\n");
        printf("Total number of computer moves: %d\n", pc_move_number);
        // Wait until user press any key
        while(getchar() == ' ');
        getchar();
        goto menu;
    case 3: 
        reset_terminal();
        // Create new random puzzle
        newpuzzle = create_random_puzzle();
        print_puzzle(&newpuzzle);
        printf("\n");
        srand(time(NULL));
        // Auto finish
        pc_move_number = auto_finish(&newpuzzle, 0);
        printf("\nComputer finished the game.\n");
        printf("Total number of computer moves: %d\n", pc_move_number);
        // Wait until user press any key
        while(getchar() == ' ');
        getchar();
        goto menu;

    case 4:
        // Take current best score
        scorefile = fopen("best_score.txt", "r");
        if (scorefile == NULL)
        {
            printf("File cannot opened!\n");
        }
        fscanf(scorefile, "%d", &best_score);
        fclose(scorefile);
        printf("\nThe best score is %d...\n", best_score);
        // Wait until user press any key
        while(getchar() == ' ');
        getchar();
        goto menu;
    case 5:
        printf("\nProgram terminated...\n");
        // Wait until user press any key
        while(getchar() == ' ');
        getchar();
        return 0;
    default:
        printf("Please enter an invalid option!\n");
        // Wait until user press any key
        while(getchar() == ' ');
        getchar();
        goto menu;
    }
}