#include <stdio.h>
#include "util.h"

#define MAX_ARRAY_SIZE 100
#define MAX_STRING_SIZE 20

/*----- MAIN ------*/
int main(){

    // Names of files
    char products[] = "products.txt";
    char stocks[] = "stocks.txt";

    // An 2D array for report 
    double filtered_pId_price_stock[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    // Fill array with -1 for understand empty cells
    for(int i=0; i<MAX_ARRAY_SIZE; i++) {
        for(int j=0; j<MAX_ARRAY_SIZE; j++) {
            filtered_pId_price_stock[i][j] = -1;
        }
    }
    
    int operation, report_flag = 0;
    // User menu
    main_menu:
    //reset_terminal();
    printf("Welcome operator, please select an option to continue: \n1- File Operations\n2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n6- Exit\n");
    scanf("%d", &operation);
    // Operation switch
    switch (operation)
    {
    case 1:
        reset_terminal();
        file_operations(products, stocks);
        goto main_menu;
    case 2:
        reset_terminal();
        search_product(products);
        goto main_menu;
    case 3:
        reset_terminal();
        check_stock_status(stocks);
        goto main_menu;
    case 4:
        reset_terminal();
        brand_stock_control(products, stocks, filtered_pId_price_stock);
        while(getchar() == ' ');
        getchar();
        report_flag = 1;
        goto main_menu;
    case 5:
        reset_terminal();
        if (report_flag){
            stock_report(filtered_pId_price_stock);
            printf("Report creted.");
        }
        else    printf("Please create report(4- Stock control by brand) before export!");
        while(getchar() == ' ');
        getchar();
        goto main_menu;
    case 6:
        return 0;
    default:
        printf("Please enter valid operation!");
        while(getchar() == ' ');
        getchar();
        goto main_menu;
        break;
    }
}