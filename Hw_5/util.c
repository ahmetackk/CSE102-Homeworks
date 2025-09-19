#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "util.h"

double colors[5][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0.5, 0.5, 0}, {0.5, 0.4, 0.2} };

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

// mixColors funtion for Part 2 which mix two colors and returns mixed colors vectors
void mix_colors(Color color1, Color color2, double *mixed_color){
    mixed_color[0] = (colors[color1][0] + colors[color2][0]) / 2;
    mixed_color[1] = (colors[color1][1] + colors[color2][1]) / 2;
    mixed_color[2] = (colors[color1][2] + colors[color2][2]) / 2;
}

// color mixer function for Part 2
Color colorMixer(Color color1, Color color2, Color *mix_colors(Color, Color, double*)){
    // Mix colors and take mixed vectors
    double mixed_color[3];
    mix_colors(color1, color2, mixed_color);
    // Variables for use during finding closest color
    double distances[5], min_distance;
    // Fşnd distance by  using Euclidean distance
    for (int i = 0; i < 5; i++){  
        distances[i] = sqrt(pow(mixed_color[0] - colors[i][0], 2) + 
                           pow(mixed_color[1] - colors[i][1], 2) + 
                           pow(mixed_color[2] - colors[i][2], 2) );
    }
    
    min_distance = distances[0];
    Color mixed_color_en = RED;
    // Find closest color
    for (int i = 1; i < 5; i++){
        if (distances[i] < min_distance){
            min_distance = distances[i];
            mixed_color_en = i;
        }
    }
    // Return found color
    return mixed_color_en;
}

// read_color func for taking color from user in Part 2
int read_color(char c){
    switch (c)
    {
    case 'r':
        return 0;
        break;
    case 'g':
        return 1;
        break;
    case 'b':
        return 2;
        break;
    case 'y':
        return 3;
        break;
    case 'o':
        return 4;
        break;
    default:
        return 0;
        break;
    }
}

// matrix_drawer for Part 3 
void matrix_drawer(int matrix[3][3]){
    // For each row
    for (int i = 0; i < 3; i++)
    {   
        // For each column
        for (int j = 0; j < 3; j++)
        {   
            // 0 for empty - 1 for X - 2 for O
            if (matrix[i][j] == 1) printf("X ");
            else if (matrix[i][j] == 2) printf("O "); 
            else printf("_ ");
        }
        printf("\n");
    }
    
}

// check_win_status func for Part 3
int check_win_status(int matrix[3][3]){
    // Horizontal win condition control
    for (int i = 0; i < 3; i++)
    {    
        if (matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2] && matrix[i][1] == matrix[i][2] && matrix[i][0] != 0) {
            return matrix[i][0];
        }
    }
    // Vertical win condition control
    for (int i = 0; i < 3; i++)
    {   
        if (matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i] && matrix[1][i] == matrix[2][i] && matrix[0][i] != 0) {
            return matrix[0][i];        
        }
    }
    // Diagonal win condition control
    if (matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2] && matrix[1][1] == matrix[2][2] && matrix[0][0] != 0){
        return matrix[1][1];
    } 
    if (matrix[0][2] == matrix[1][1] && matrix[0][2] == matrix[2][0] &&  matrix[1][1] == matrix[2][0] && matrix[1][1] != 0) {
        return matrix[1][1]; 
    }
    return 0;
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

// Part 1
void letter_frequency_finder(){
    // Variables
    char filename[20];
    int letter_frequence[26];
    // Letter catalog
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Fill letter_frequence array with 0 
    for (int i = 0; i < 26; i++)
    {
        letter_frequence[i] = 0;
    }
    // Take file name from user
    printf("Enter the file name: ");
    scanf("%s", filename);

    // Open file
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File cant opened.");
        return 0;
    }

    // Get char for start reading
    char c = getc(file);
    // While file is not end
    while (c != EOF)
    {   
        // ASCII value intervals for English characters
        if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
            for (int i = 0; i < 26; i++)
            {   
                // Increase counter for letter
                if (c == letters[i] || c == letters[i] + 32)
                {
                    letter_frequence[i]++;
                }
            }
            
        }
        // Take new char
        c = getc(file);
    }
    
    // Print letter frequencies
    printf("Letter Frequency:\n");
    for (int i = 0; i < 26; i++)
    {
        if (letter_frequence[i] != 0)
        {
            printf("%c: %d\n", letters[i], letter_frequence[i]);
        }
    }
    
}

// Part 2
void mixing_colors(){
    // Variables
    Color color1, color2;
    char c;

    // Take colors from user
    printf("Enter color 1 (r, g, b, y, o): ");
    scanf(" %c", &c);
    color1 = read_color(c);

    printf("Enter color 2 (r, g, b, y, o): ");
    scanf(" %c", &c);
    color2 = read_color(c);

    // Mix colors
    Color mixed_color = colorMixer(color1, color2, mix_colors);

    // Write mixed color
    printf("Mixed color: ");
    switch(mixed_color) {
        case RED:
            printf("RED");
            break;
        case GREEN:
            printf("GREEN");
            break;
        case BLUE:
            printf("BLUE");
            break;
        case YELLOW:
            printf("YELLOW");
            break;
        case ORANGE:
            printf("ORANGE");
            break;
        default:
            printf("Unknown color\n");
            break;
    }
}

// Part 3
void tic_tac_toe(){
    // Variables and matrix for table
    int matrix[3][3];
    int sequence = 1;
    int row_move, col_move; 

    // Fill matrix with 0 for understand empty cells
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) 
            matrix[i][j] = 0;

    // While nobody winning keep contiune playing
    while(check_win_status(matrix) == 0)
    {      
        // If table is full that means game is draw
        if (sequence == 10)
        {
            printf("Game is draw!\n");
            getchar();
            return 0;
        }
        // Take moves from users
        if (sequence % 2 == 1) printf("Player 1 (X), enter your move (row, col): ");
        if (sequence % 2 == 0) printf("Player 1 (O), enter your move (row, col): ");

        take_move:
        scanf("%d %d", &row_move, &col_move);

        // If taken cell is empty fill matrix according to taken move
        if (matrix[row_move][col_move] == 0){
            if (sequence % 2 == 1){
                matrix[row_move][col_move] = 1;
            }
            else{
                matrix[row_move][col_move] = 2;
            }
        }
        // Else give error
        else{
            printf("Please enter empyt cell!\n");
            goto take_move;
        }
        // Draw matrix
        matrix_drawer(matrix);
        sequence++;
    }

    // After win print winner
    if (check_win_status(matrix) == 1) printf("Player 1 (X) wins!");
    else printf("Player 2 (O) wins!");
    
}
