#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "util.h"

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

// Clear terminal
void reset_terminal(){
    printf("\033[2J");
    printf("\033[0;0f");
}

const char* menu_element_string(int a){
    switch (a)
    {
    case 1:
        return "Kebap";
    case 2:
        return "Lahmacun";
    case 3:
        return "Pide";
    case 4:
        return "Doner";
    case 5:
        return "Kola";
    case 6:
        return "Su";
    case 7:
        return "Kunefe";
    case 8:
        return "Sutlac";
    default:
        break;
    }
}

const char* choice_string(int a){

    if (a == 1)
    {
        return "Stone";
    }
    if (a == 2)
    {
        return "Paper";
    }
    if (a == 3)
    {
        return "Scissors";
    }

}

void space(int a){
    for (int i = 0; i < a; i++)
    {   
        printf(" ");
    }
}

int rpc_win_statue(int choice, int computer_choice){

    // If choice is Stone
    if (choice == 1)
    {
        // Paper will won Scissors will lose
        if (computer_choice == 2)
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    // If choice is Paper
    if (choice == 2)
    {
        // Scissors will won Rock will lose
        if (computer_choice == 3)
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    // If choice is Scissors
    if (choice == 3)
    {
        // Paper will lose Rock will won
        if (computer_choice == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }

    }

}

void read_file(){

    int length = 0;
    char a;
    FILE *menufile;
    menufile = fopen("menu.txt", "r");

    char c = getc(menufile);

    while(c != EOF)
    {
        if (c == '\n')
        {   
            printf("\n");
            length = 0;
        }
        else if (c == ' ')
        {   
            for (int i = 0; i < 10 - length; i++)
            {
                printf(" ");
            }
            printf("\t");
        }
        else
        {
            printf("%c", c);
            length++;
        }

        c = getc(menufile);
    }

    fclose(menufile);

}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

void rock_paper_scissors(){
    // 1-Stone 2-Paper 3-Scissors
    int choice;
    char contiune_statue;

    game_start:
    reset_terminal();

    srand(time(0));
    int computer_choice = ((rand() % 3) + 1);

    printf("Please make a choice!\n");
    printf("1: Stone, 2: Paper, 3: Scissors\n");

    scanf("%d", &choice);

    printf("You chose %s. I chose %s. ", choice_string(choice), choice_string(computer_choice));

    if (choice == computer_choice)
    {
        printf("It's a tie!\n");
    }
    else
    {
        if (rpc_win_statue(choice, computer_choice) == 1)
        {
            printf("You won!\n");
        }
        else
        {
            printf("You lose!\n");
        }
    }

    printf("Do you want to play again? (Y/N): ");
    scanf(" %c", &contiune_statue);

    if (contiune_statue == 'Y' || contiune_statue == 'y')
    {
        goto game_start;
    }
    else if (contiune_statue == 'N' || contiune_statue == 'n')
    {
        return 0;
    }
}

void order_menu(){

    FILE *bill;
    int choice, piece;
    char student_state;
    float total_price, student_discount, total_price_vat, discount;
    int order[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    float menu[8] = {75.99, 21.50, 40.00, 55.60, 15.00, 5.00, 60.00, 32.50};

    read_file();

    bill = fopen("bill.txt", "w+");
    
    printf("\nFood Menu: ");
    printf("\n1. Kebap");
    printf("\n2. Lahmacun");
    printf("\n3. Pide");
    printf("\n4. Doner");
    printf("\n5. Kola");
    printf("\n6. Su");
    printf("\n7. Kunefe");
    printf("\n8. Sutlac");
    printf("\n0. Finish Order\n");

    take_order:
    printf("Please choose a product (1-8): ");
    scanf("%d", &choice);

    if (choice != 0)
    {
        printf("How many servings do you want? ");
        scanf("%d", &piece);

        order[choice] = piece;

        goto take_order;
    }
    

    student:
    printf("Are you student? (Y/N): ");
    while (getchar() == ' ');
    scanf("%c", &student_state);

    if (student_state != 'Y' && student_state != 'y' && student_state != 'N' && student_state != 'n')
    {
        printf("Please enter valid input!\n");
        goto student;
    }
    
    fprintf(bill, "220104004061");
    fprintf(bill, "\t\t");

    // time_t t = time(NULL);
    // struct tm tm = *localtime(&t);
    // fprintf(bill, "%02d.%02d.%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    // fprintf(bill, "/%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

    fprintf(bill, "\n------------------------------------\n");
    fprintf(bill, "Product \t\t Price (TL)"); 
    fprintf(bill, "\n------------------------------------\n");


    for (int i = 0; i < sizeof(menu); i++)
    {
        if (order[i] != 0)
        {   
            total_price += (float)order[i] * menu[i];
            fprintf(bill, "%d* %s \t\t %.2f\n", order[i], menu_element_string(i), (float)order[i] * menu[i]);
        }
    }

    fprintf(bill, "Total: \t\t %.2f\n", total_price);

    if (student_state == 'Y' ||student_state == 'y')
    {
        student_discount = (total_price * 12.5 / 100.0);
        fprintf(bill, "Student discount: \t\t -%.2f", student_discount);
        total_price -= student_discount;
    }
    else
    {   
        if(total_price >= 150)
        {
            discount = (total_price * 10.0 / 100.0);
            fprintf(bill, "150 TL discount: \t\t -%.2f", discount);
            total_price -= discount;
        }
    }
    
    fprintf(bill, "\n------------------------------------\n");
    fprintf(bill, "Price: \t\t %.2f\n", total_price);

    total_price_vat = total_price + (total_price * 18.0 / 100.0);
    fprintf(bill, "Price + VAT: \t\t %.2f\n", total_price_vat);

    fclose(bill);

}
