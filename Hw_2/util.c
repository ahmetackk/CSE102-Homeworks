#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "util.h"

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

/* Take power of 10  for calc_operation() */
int pow_10(int power)
{   
    int number = 1;

    /* Multiply power times 10*/
    for (int i = 0; i < power; i++)
    {
        number = number * 10;
    }
    return number;
}

/* Factorial function for calc_operation() */
int factorial(int number){
    int result = 1;

    for (int i = 2; i <= number; i++)
    {
        result = i * result;
    }
    return result;
}

/* Make calculation for enchanced_calculator() */
float calc_operation(){
    char operation;
    // Take operation from user
    printf("Enter the operation(+,-,/,*,!,^): ");
    scanf(" %c", &operation);

    int operand1, operand2;

    // Switch case operations and return result
    switch (operation)
    {
    case '+':
        printf("Enter the first operand: ");
        scanf("%d", &operand1);
        printf("Enter the second operand: ");
        scanf("%d", &operand2);
        printf("%d+%d=", operand1, operand2);
        
        return (float)(operand1 + operand2);
    
    case '-':
        printf("Enter the first operand: ");
        scanf("%d", &operand1);
        printf("Enter the second operand: ");
        scanf("%d", &operand2);
        printf("%d-%d=", operand1, operand2);

        return (float)(operand1 - operand2);
    
    case '/':
        printf("Enter the first operand: ");
        scanf("%d", &operand1);
        printf("Enter the second operand: ");
        scanf("%d", &operand2);
        printf("%d/%d=", operand1, operand2);

        return (float)((float)operand1 / (float)operand2);
    
    case '*':
        printf("Enter the first operand: ");
        scanf("%d", &operand1);
        printf("Enter the second operand: ");
        scanf("%d", &operand2);
        printf("%dx%d=", operand1, operand2);

        return (float)(operand1 * operand2);
    
    case '%':
        printf("Enter the first operand: ");
        scanf("%d", &operand1);
        printf("Enter the second operand: ");
        scanf("%d", &operand2);
        printf("%d%%%d=", operand1, operand2);

        return (float)(operand1 % operand2);

    case '!':
        printf("Enter the operand: ");
        scanf("%d", &operand1);
        printf("%d!=", operand1);

        return (float)factorial(operand1);

    case '^':
        printf("Enter the first operand: ");
        scanf("%d", &operand1);
        printf("Enter the second operand: ");
        scanf("%d", &operand2);
        printf("%d^%d=", operand1, operand2);

        return (float)pow(operand1, operand2);
        
    default:
        printf("Wrong operation!");
        break;
    }
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

/* Part 1*/
void leap_year(){
    int year;
    
    // Take a year from user
    printf("Please enter a year: ");
    scanf("%d", &year);

    // If years mod 4 is equal 0 then the year is leap year
    if(year % 4 == 0){
        printf("%d is a leap year\n", year);
    }
    else{
        printf("%d is not a leap year\n", year);
    }
}

/* Part 2 */
void enchanced_calc(){
    char outputformat;
    float result;

    error2:
    // Take result format from user
    printf("Enter the format of output (S or I): ");
    scanf(" %c", &outputformat);

    if(outputformat == 'I'){
        // If format is show as integer only
        result = calc_operation();
        printf("%d", (int)result);
    }
    else if (outputformat == 'S'){
        // If format is S then show scientific format
        int m, n, digit, leftside, rightside;
        // Take m and n values
        error1:
        printf("Enter m and n values: ");
        scanf("%d %d", &m, &n);
        // If n is more than m give an error
        if (n > m)
        {
            printf("N is can not be more than m!\n");
            goto error1;
        }
        // Calculate result
        result = calc_operation();
        // Variables for print 
        int numbers_power = 0;
        float tempresult = result;

        // If result is not float or not have power 10
        if (fmod(tempresult, 10.0) == 0)
        {   
            // Multiply by 10 until it have power 10
            while (fmod(tempresult, 10.0) == 0)
            {
                tempresult = tempresult / 10;
                numbers_power++;
            }

            numbers_power = -numbers_power;
            // Now you found number as an integer with power 10 
        }
        else
        {   
            // If number is float then multiply by 10 until it becames integer
            while (fmod(tempresult, 10.0) != 0)
            {
                tempresult = tempresult * 10;
                numbers_power++;
            }

            tempresult = tempresult / 10;
            numbers_power--;
            // Now you found number as an integer with power 10
        }

        // Find left side of dot (Example 12.34 ---> 12)
        leftside = (int)(tempresult / pow_10(n));
        // Find right side of dot (Example 12.34 ---> 34)
        rightside = tempresult - (leftside * pow_10(n));

        // Print right side
        printf("%0*d", m - n, leftside);
        // Print dot
        printf(".");
        // Print left side
        printf("%0*d", n, rightside);
        // Print power 10
        printf("e%d\n", n - numbers_power);
    }
    else
    {
        // Give error if there is undefined format
        printf("Error! Undefined format");
        goto error2;
    }
}

/* Part 3 */
void grade_calculator(){
    // Variables
    int exam1, exam2, exam3, assigment1, assigment2;
    float finalgrade;
    // Take exam grades from user
    printf("Enter 3 exam grades of student: ");
    scanf("%d %d %d", &exam1, &exam2, &exam3);
    // Take assignment grades from user
    printf("Enter 2 assignment grades of student: ");
    scanf("%d %d", &assigment1, &assigment2);
    // Calculate final grade
    finalgrade = ((exam1 + exam2 + exam3) / 3 * 0.6 ) + ((assigment1 + assigment2) / 2 * 0.4 );
    // If final grade is more than or equal to 60 passed 
    if(finalgrade >= 60)
    {
        printf("Final grade: %.1f Passed!", finalgrade);
    }
    else
    {   // Else failed
        printf("Final grade: %.1f Failed!", finalgrade);
    }
}