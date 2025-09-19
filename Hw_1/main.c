#include <stdio.h>

/* ------------------------ AUXILIARY FUNCTIONS --------------------------------- */

/* GCD find function for gcd_writer() */
int gcd_finder(int number1, int number2){
    /* Check are the numbers equal */
    if(number1 == number2){ 
        return number1;     // If numbers are equal by the Euclidean algorithm remainder will be zero thats why GCD is found
    }
    else{
        /* If numbers are not equal */
        while(number1 > number2){
            number1 = number1 - number2;    // Substract number2 from number1 until reminder is less than number2      
        }
        return gcd_finder(number2, number1);    // By the Euclidean algorithm repeat same process until found GCD
    }
}

/* Digit founder function for multiple() */
void digit_finder(int number, int array[3]){

    /* This function takes numbers digits to an array up to nuber with 3 digits*/

    /* Variables */
    int digit_multiplier = 100;
    int digits[3];

    float division;

    /* Divide 100 for digit 3 and send array */
    division = (float)number / (float)digit_multiplier;
    digits[2] = (int)division; 
    /* After taking 3rd digit substract 3rd digit from number */
    number = number - (digit_multiplier * (int)division); 
    digit_multiplier = digit_multiplier / 10;   // Make digit_multiplier 10 

    /* Divide 10 for digit 2 and send array */
    division = (float)number / (float)digit_multiplier; 
    digits[1] = (int)division;
    /* After taking 2nd digit substract 2nd digit from number */
    number = number - (digit_multiplier * (int)division);
    digit_multiplier = digit_multiplier / 10;   // Make digit_multiplier 1

    /* After substracting 2nd digit from number send array 1st digit*/
    digits[0] = number;

    /* Until numbers digits start make arrays index -1 for understanding numbers digits isnt started yet*/
    int i = 2;
    while(digits[i] == 0){
        digits[i] = -1;
        i--;
    }

    /* Send digit array to taken array */
    for(int i = 0; i < 3; i++){
        array[i] = digits[i];
    }
    
}

/* ----------------------------------------------------------------------------------- */


/* ------------------------------ MAIN FUNCTIONS ------------------------------------- */

/* Part 1 */
void gcd_writer(){
    /* Variables */
    int num1, num2, gcd;

    /* Take variables from user*/
    printf("Enter a number: ");
    scanf("%d", &num1);
    printf("Enter another number: ");
    scanf("%d", &num2);

    /* Send numbers to gcd_finder() in order of magnitude*/
    if(num1 > num2){
        gcd = gcd_finder(num1, num2);
    }
    else{
        gcd = gcd_finder(num2, num1);
    }

    /* Print gcd */
    printf("GCD is: %d", gcd);

}

/* Part 2 */
void sum(){
    /* Variables */
    int num1, num2;

    /* Take variables from user*/
    printf("First number : ");
    scanf("%d", &num1);
    printf("Second number: ");
    scanf("%d", &num2);

    /* Print numbers sums as the arithmetic done */
    printf("Result:\n");
    printf("   %4d\n", num1);   // Assumed numbers will have at most 4 valid digits
    printf("   %4d\n", num2);
    printf("+\n");
    printf("-------\n");
    printf("   %4d", num1 + num2);  // Print their sums
}

/* Part 3 */
void multiple(){
    /* Variables */
    int num1, num2, digits[3];

    /* Take variables from user */
    printf("First number : ");
    scanf("%d", &num1);
    printf("Second number: ");
    scanf("%d", &num2);

    /* Print numbers multiples as if done manually on paper */
    printf("Result:\n");
    printf("       %3d\n", num1);
    printf("       %3d\n", num2);
    printf("x\n");
    printf("----------\n");

    /* If number1 or number2 is equal to 0 then write 0 to result */
    if(num2 == 0 || num1 == 0){
        printf("         0\n");
    }
    else if((num1 / 10) < 1 || (num2 / 10) < 1){
        /* If one or both of them are 1 digit then just print their multiple */
        printf("     %5d\n", num1 * num2);
    }
    else{
        /* Else multiple number1 with number2's digits seperately*/
        int i = 0;
        int space = 6;  // Space size for print
        digit_finder(num2, digits); // digit_finder for number2

        /* While i is less than 3 and until numbers digits finish */
        while(digits[i] != -1 && i < 3){    
            for(int j = 0; j < space; j++){
                printf(" ");
            }
            printf("%4d\n", num1 * digits[i]);  // Print multiple of number1 and number2's digits
            i++;        // Increase i for other digit
            space--;    // Decrease space size for print
        }
        /* Print last part of multiple */
        printf("+\n");
        printf("----------\n");
        printf("     %5d\n", num1 * num2);
    }
}

/* Part 4 */
void between_1_10(){
    
    int number; // Variable

    /* Take varible from user */
    printf("Plese enter a integer between 5 and 10 (inclusive): ");
    scanf("%d", &number);

    /* If variable is not between 1 and 10 give an error */
    if(number < 1 || number > 10){
        printf("Invalid input.");
    }
    else{
        /* Else control number */
        if(number > 5){
            /* If number is more than 5 */
            printf("The integer you entered is greater than 5");
        }
        if(number <=5){
            /* If number is small or equal 5 */
            printf("The integer you entered is less than or equal to 5");
        }
    }
}

/* --------------------------------------------------------------------------------- */

int main(){
    /* Call the parts in order */
    printf("--Part 1--\n");
    gcd_writer();
    printf("\n");
    printf("--Part 2--\n");
    sum();
    printf("\n");
    printf("--Part 3--\n");
    multiple();
    printf("\n");
    printf("--Part 4--\n");
    between_1_10();
}