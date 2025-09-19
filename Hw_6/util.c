#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_ARRAY_SIZE 100
#define MAX_STRING_SIZE 20

#include "util.h"

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

// Reset terminal for clean image
void reset_terminal(){
    printf("\033[2J");
    printf("\033[0;0f");
}

/*--------- Part 2 functions ----------------*/

// Add product
void add_product(char filename[]){
    // Open file
    FILE *file ;
    file = fopen(filename, "r+");
    // Variables
    char type, name[MAX_STRING_SIZE], brand[MAX_STRING_SIZE], c;
    double price;
    int pId = 1;
    // Go to files end and take new pId for add 
    while ((c = getc(file)) != EOF)
    {
        if (c == '\n') pId++; 
    }
    // Take product from user
    printf("Add new product (Type, Name, Brand, and Price): ");
    scanf(" %c,%[^,],%[^,],%lf", &type, &name, &brand, &price);
    fprintf(file, "\n%d,%c,%s,%s,%.1f", pId + 1, type, name, brand, price);

    fclose(file);
}

// Delete product
void delete_product(char filename[]){

    int delete_pId; 
    // Take pId from user
    printf("Please select which pId you want to delete: ");
    scanf("%d", &delete_pId);
    // Open files
    FILE *file ;
    file = fopen(filename, "r+");
    FILE *tempfile;
    tempfile = fopen("temp.txt", "w+");
    // Variables
    int pId = 1, line_number = 0;
    char linebuffer[MAX_ARRAY_SIZE], c;
    char type, name[MAX_STRING_SIZE], brand[MAX_STRING_SIZE];
    double price;
    int temp_pId;
    // Until find target pId scan and print new file
    while (pId < delete_pId)
    {
        fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price);
        fprintf(tempfile, "%d,%c,%s,%s,%.1f\n", temp_pId , type, name, brand, price);
        pId++;
    }
    // When found just scan for delete in new file 
    fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price);
    // Keep going print to new file
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price) == 5)
    {   
        fprintf(tempfile, "%d,%c,%s,%s,%.1f\n", temp_pId - 1 , type, name, brand, price);
        pId++;
    }
    // Close new file
    fclose(tempfile);
    tempfile = fopen("temp.txt", "r+");

    // Clear last empty line from new file for prevent any error
    FILE *tempprod;
    tempprod = fopen("tempprod.txt", "w+");

    fscanf(tempfile, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price);
    fprintf(tempprod, "%d,%c,%s,%s,%.1f", temp_pId , type, name, brand, price);
    while (fscanf(tempfile, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price) == 5)
    {   
        fprintf(tempprod, "\n%d,%c,%s,%s,%.1f", temp_pId, type, name, brand, price);
    }

    fclose(file);
    fclose(tempfile);
    fclose(tempprod);

    // Rename new file as products.txt and delete old one
    remove("products.txt");
    remove("temp.txt");
    rename("tempprod.txt", "products.txt");
}

// Update product
void update_product(char filename[]){
    // Variables
    char type, name[MAX_STRING_SIZE], brand[MAX_STRING_SIZE], up_type, up_name[MAX_STRING_SIZE], up_brand[MAX_STRING_SIZE];
    double price, up_price;
    int pId, temp_pId;
    // Take update commands
    printf("Update product(Please enter pID, Type, Name, Brand, and Price): ");
    scanf("%d,%c,%[^,],%[^,],%lf", &pId, &up_type, &up_name, &up_brand, &up_price);
    // Open files
    FILE *file ;
    file = fopen(filename, "r+");
    FILE *tempfile;
    tempfile = fopen("temp.txt", "w+");

    // If user want update first line begin with printing updated data to new file
    if (pId == 1)
    {
        fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price);
        fprintf(tempfile, "%d,%c,%s,%s,%.1f", temp_pId , up_type, up_name, up_brand, up_price);
        while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price) == 5)
        {
            fprintf(tempfile, "\n%d,%c,%s,%s,%.1f", temp_pId, type, name, brand, price);
        }
    }
    // Else 
    else
    {   
        // Scan file until found target pId
        fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price);
        fprintf(tempfile, "%d,%c,%s,%s,%.1f", temp_pId, type, name, brand, price);
        while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price) == 5)
        {   
            // If target pId found print updated data to new file
            if (temp_pId == pId)
            {
                fprintf(tempfile, "\n%d,%c,%s,%s,%.1f", temp_pId , up_type, up_name, up_brand, up_price);
            }
            // Else just print old one
            else{
                fprintf(tempfile, "\n%d,%c,%s,%s,%.1f", temp_pId, type, name, brand, price);
            }
            
        }
    }

    fclose(file);
    fclose(tempfile);
    // Remove old file and rename new file
    remove("products.txt");
    rename("temp.txt", "products.txt");

}

// Add new stock
void add_new_stock(char filename[]){
    // Open file
    FILE *file ;
    file = fopen(filename, "r+");

    // Variables
    char type, branch[MAX_STRING_SIZE], c;
    int sId = 1, current_stock, pId;

    // Go to files end and take new sId for add  
    while ((c = getc(file)) != EOF)
    {
        if (c == '\n') sId++; 
    }

    // Take datas from user
    printf("Add new stock (pID, Branch, and Current Stock): ");
    scanf("%d,%[^,],%d", &pId, &branch, &current_stock);
    fprintf(file, "\n%d,%d,%s,%d", sId + 1, pId, branch, current_stock);

    fclose(file);
}

// Delete stock
void delete_stock(char filename[]){

    int delete_sId;

    // Take target pId for delete
    printf("Please select which pId you want to delete: ");
    scanf("%d", &delete_sId);

    // Open files
    FILE *file ;
    file = fopen(filename, "r+");
    FILE *tempfile;
    tempfile = fopen("temp.txt", "w+");

    // Variables
    char linebuffer[MAX_ARRAY_SIZE], c, branch[MAX_STRING_SIZE];
    int sId = 1, current_stock, pId, line_number = 0;
    double price;
    int temp_sId;

    // Until find target pId scan and print new file 
    while (sId < delete_sId)
    {
        fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock);
        fprintf(tempfile, "%d,%d,%s,%d\n", temp_sId, pId, branch, current_stock);
        sId++;
    }
    // When found just scan for delete
    fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock);
    // Keep going printing to new file
    while (fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock) == 4)
    {   
        fprintf(tempfile, "%d,%d,%s,%d\n", temp_sId, pId, branch, current_stock);
        sId++;
    }
    
    // Close file
    fclose(tempfile);
    tempfile = fopen("temp.txt", "r+");

    // Clear last empty line from new file for prevent any error
    FILE *tempstocks;
    tempstocks = fopen("tempstocks.txt", "w+");

    fscanf(tempfile, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock);
    fprintf(tempstocks, "%d,%d,%s,%d", temp_sId, pId, branch, current_stock);
    while (fscanf(tempfile, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock) == 4)
    {   
        fprintf(tempstocks, "\n%d,%d,%s,%d", temp_sId, pId, branch, current_stock);
    }

    fclose(file);
    fclose(tempfile);
    fclose(tempstocks);

    // Delete old files and rename new one as stocks.txt
    remove("stocks.txt");
    remove("temp.txt");
    rename("tempstocks.txt", "stocks.txt");
}

// Update stock
void update_stock(char filename[]){

    // Variables
    char branch[MAX_STRING_SIZE], up_branch[MAX_STRING_SIZE];
    int pId, up_pId, temp_sId, current_stock, up_current_stock, sId;

    // Take datas from user
    printf("Update stock(Please enter sID, pID, Branch, and Current Stock): ");
    scanf("%d,%d,%[^,],%d", &sId, &up_pId, &up_branch, &up_current_stock);

    // Open files
    FILE *file ;
    file = fopen(filename, "r+");
    FILE *tempfile;
    tempfile = fopen("temp.txt", "w+");

    // If user want update first line begin with printing updated data to new file
    if (sId == 1)
    {
        fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock);
        fprintf(tempfile, "%d,%d,%s,%d", temp_sId, pId, branch, current_stock);
        while (fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock) == 4)
        {
           fprintf(tempfile, "\n%d,%d,%s,%d", temp_sId, pId, branch, current_stock);
        }
    }
    else
    {   
        // Scan file until found target pId
        fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock);
        fprintf(tempfile, "%d,%d,%s,%d", temp_sId, pId, branch, current_stock);
        while (fscanf(file, "%d,%d,%[^,],%d", &temp_sId, &pId, &branch, &current_stock) == 4)
        {
            if (temp_sId == sId)
            {   
                // If found print new data
                fprintf(tempfile, "\n%d,%d,%s,%d", temp_sId , up_pId, up_branch, up_current_stock);
            }
            else{
                // Else just print old one
                fprintf(tempfile, "\n%d,%d,%s,%d", temp_sId, pId, branch, current_stock);
            }
            
        }
    }

    fclose(file); 
    fclose(tempfile);
    // Remove old file and rename new file as stokcs.txt
    remove("stocks.txt");
    rename("temp.txt", "stocks.txt");
}

/*------------------ Part 3 functions --------------------*/

// List products
void list_products(char filename[]){
    reset_terminal();
    // Open file
    FILE *file;
    file = fopen(filename, "r+");
    // Variables
    int temp_pId;
    char type, name[MAX_STRING_SIZE], brand[MAX_STRING_SIZE];
    double price;

    // Print products 
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &temp_pId, &type, &name, &brand, &price) == 5)
    {
        printf("%d,%c,%s,%s,%.1f\n", temp_pId , type, name, brand, price);
    }
    
    fclose(file);
}

// Filter products
void filter_products(char filename[]){
    // Open files
    FILE *file;
    file = fopen(filename, "r+");
    // Variables
    char f_type[5];
    char f_name[MAX_STRING_SIZE], f_brand[MAX_STRING_SIZE];
    double f_price_max, f_price_min;

    // Menu
    filter_menu:
    reset_terminal();
    // Take filter data from user
    printf("Please enter type of filter(type,name,brand,min price,max price exmp: (type,name,Samsung,10,20)): ");
    scanf("%[^,],%[^,],%[^,],%lf,%lf", &f_type, &f_name, &f_brand, &f_price_min, &f_price_max);
    // If min price entered bigger than max price take data again
    if (f_price_min > f_price_max)
    {
        printf("Minimum price cannot be bigger than maximum price!");
        while(getchar() == ' ');
        getchar();
        goto filter_menu;
    }

    // Variables for read
    int pId;
    char type[5], name[MAX_STRING_SIZE], brand[MAX_STRING_SIZE];
    double price;
    // Variables for filtering
    int filtered_pId[MAX_ARRAY_SIZE];
    char filtered_type[MAX_ARRAY_SIZE][5], filtered_name[MAX_ARRAY_SIZE][MAX_STRING_SIZE], filtered_brand[MAX_ARRAY_SIZE][MAX_STRING_SIZE];
    double filtered_price[MAX_ARRAY_SIZE];
    int filtered = 0;

    // Scan and filter
    while ((fscanf(file, "%d,%[^,],%[^,],%[^,],%lf", &pId, &type, &name, &brand, &price)) == 5)
    {   
        if (price <= f_price_max && price >= f_price_min){
            if (strcmp(f_type, "type") == 0 || strcmp(type, f_type) == 0){
                if (strcmp(f_name, "name") == 0 || strcmp(name, f_name) == 0){
                    if (strcmp(f_brand, "brand") == 0 || strcmp(brand, f_brand) == 0){
                        // If filter is done take variables to array
                        filtered_pId[filtered] = pId;
                        strcpy(filtered_type[filtered], type);
                        strcpy(filtered_name[filtered], name);
                        strcpy(filtered_brand[filtered], brand);
                        filtered_price[filtered] = price;
                        filtered++;
                    }
                }
            }
        }       
    }

    // If none of products is not fit the filter print
    if (filtered == 0)
    {
        printf("Cannot found any stock.\n");
    }
    else
    {   
        // If any data fits the filter then print product
        for (int i = 0; i < filtered; i++)
        {
            printf("%d,%s,%s,%s,%.1f\n", filtered_pId[i], filtered_type[i], filtered_name[i], filtered_brand[i], filtered_price[i]);
        }
        
    }

    fclose(file);
}

/*-------------- Part 4 functions ---------------*/

// List product stock according to branch
void list_product_stock_branch(char filename[]){
    // Variables
    char f_branch[MAX_STRING_SIZE];
    int f_pId;

    reset_terminal();
    // Take branch and pID from user
    printf("Please enter product ID and branch name(2,Istanbul): ");
    scanf("%d,%s", &f_pId, &f_branch);

    // Open file
    FILE *file;
    file = fopen(filename, "r+"); 

    // Variables for read
    char  branch[MAX_STRING_SIZE], up_branch[MAX_STRING_SIZE];
    int pId, current_stock, sId;

    // Variables for filter
    char filtered_branch[MAX_ARRAY_SIZE][MAX_STRING_SIZE];
    int filtered_pId[MAX_ARRAY_SIZE], filtered_stock[MAX_ARRAY_SIZE];
    int filtered = 0;

    // Scan until target pID found
    while (fscanf(file, "%d,%d,%[^,],%d", &sId, &pId, &branch, &current_stock) == 4)
    {   
        if (pId == f_pId){
            // If branch is also suits take datas to array
            if (strcmp(branch, f_branch) == 0){
                strcpy(filtered_branch[filtered], branch);
                filtered_pId[filtered] = pId;
                filtered_stock[filtered] = current_stock;
                filtered++;
            }
        }      
    }

    // If none of stocks is not fit the filter print
    if (filtered == 0)
    {
        printf("Cannot found any stock.\n");
    }
    else
    {
        for (int i = 0; i < filtered; i++)
        {   
            // If any data fits the filter then print stock
            printf("%d,%s,%d\n", filtered_pId[i], filtered_branch[i], filtered_stock[i]);
        }
        
    }

    fclose(file);
}

// List branchs all stocks
void list_branch_stocks(char filename[]){
    // Variables
    char f_branch[MAX_STRING_SIZE];

    reset_terminal();
    // Take branch name from user
    printf("Please enter branch name: ");
    scanf("%s", &f_branch);

    // Open file
    FILE *file;
    file = fopen(filename, "r+"); 
    
    // Variables for read
    char  branch[MAX_STRING_SIZE];
    int pId, current_stock, sId;

    // Variables for filter
    char filtered_branch[MAX_ARRAY_SIZE][MAX_STRING_SIZE];
    int filtered_pId[MAX_ARRAY_SIZE], filtered_stock[MAX_ARRAY_SIZE];
    int filtered = 0;

    // Read until target branch found
    while (fscanf(file, "%d,%d,%[^,],%d", &sId, &pId, &branch, &current_stock) == 4)
    {   
        if (strcmp(branch, f_branch) == 0){
            // If target found take datas to array
            strcpy(filtered_branch[filtered], branch);
            filtered_pId[filtered] = pId;
            filtered_stock[filtered] = current_stock;
            filtered++;
        }
    }

    // If none of stocks is not fit the filter print
    if (filtered == 0)
    {
        printf("Cannot found any stock.\n");
    }
    else
    {
        for (int i = 0; i < filtered; i++)
        {   
            // If any data fits the filter then print stock
            printf("%d,%s,%d\n", filtered_pId[i], filtered_branch[i], filtered_stock[i]);
        }
        
    }

    fclose(file);
}

// List out-of-stocks
void list_out_of_stocks(char filename[]){

    reset_terminal();
    // Open file
    FILE *file;
    file = fopen(filename, "r+"); 
    
    // Variables for read
    char branch[MAX_STRING_SIZE];
    int pId, current_stock, sId;

    // Variables for filter
    char filtered_branch[MAX_ARRAY_SIZE][MAX_STRING_SIZE];
    int filtered_pId[MAX_ARRAY_SIZE], filtered_stock[MAX_ARRAY_SIZE];
    int filtered = 0;

    // Read until out-of-stock is found
    while (fscanf(file, "%d,%d,%[^,],%d", &sId, &pId, &branch, &current_stock) == 4)
    {   
        if (current_stock == 0){
            // If found take datas to array
            strcpy(filtered_branch[filtered], branch);
            filtered_pId[filtered] = pId;
            filtered_stock[filtered] = current_stock;
            filtered++;
        }
    }

    // If none of stocks is not fit the filter print
    if (filtered == 0)
    {
        printf("Cannot found any out-of-stock.\n");
    }
    else
    {
        for (int i = 0; i < filtered; i++)
        {   
            // If any data fits the filter then print stock
            printf("%d,%s,%d\n", filtered_pId[i], filtered_branch[i], filtered_stock[i]);
        }
        
    }

    fclose(file);
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

// Part 2
int file_operations(char products[], char stocks[]){

    int fileoperation;

    file_menu:
    reset_terminal();
    // Take menu operation from user
    printf("File operations: \n1- Add producct\n2- Delete product\n3- Update product\n4- Add feature to product\n5- Add new stock\n6- Delete stock\n7- Update stock\n8- Return to main menu\n");
    scanf("%d", &fileoperation);
    // Operation switch
    switch (fileoperation)
    {
    case 1:
        reset_terminal();
        add_product(products);
        goto file_menu;
    case 2:
        reset_terminal();
        delete_product(products);
        goto file_menu;
    case 3:
        reset_terminal();
        update_product(products);
        goto file_menu;
    case 4:
        
        break;
    case 5:
        reset_terminal();
        add_new_stock(stocks);
        goto file_menu;
    case 6:
        reset_terminal();
        delete_stock(stocks);
        goto file_menu;
    case 7:
        reset_terminal();
        update_stock(stocks);
        goto file_menu;   
    case 8:
        return 0;
    default:
        printf("Please enter valid operation!");
        while(getchar() == ' ');
        getchar();
        goto file_menu;
        break;
    }
}

// Part 3
int search_product(char file[]){
    int operation;

    search_menu:
    reset_terminal();
    // Take menu operation from user
    printf("Querry Products: \n1- List all products\n2- Filter products by brand, type, price or a user-defined feature\n3- Return to main menu.\n");
    scanf("%d", &operation);
    // Menu operation switch
    switch (operation)
    {
    case 1:
        reset_terminal();
        list_products(file);
        while(getchar() == ' ');
        getchar();
        goto search_menu;
    case 2:
        reset_terminal();
        filter_products(file);
        while(getchar() == ' ');
        getchar();
        goto search_menu;
    case 3:
        return 0;
    default:
        printf("Please enter valid operation!");
        while(getchar() == ' ');
        getchar();
        goto search_menu;
        break;
    }
}

// Part 4
int check_stock_status(char stocks[]){
    int operation;

    check_stock_status_menu:
    reset_terminal();
    // Take menu operation from user
    printf("Check Stock Status: \n1- List stock of product in branch\n2- List all stocks in branch\n3- List out-of-stock products in branch\n4- Return to main menu");
    scanf("%d", &operation);
    // Operation switch
    switch (operation)
    {
    case 1:
        reset_terminal();
        list_product_stock_branch(stocks);
        while(getchar() == ' ');
        getchar();
        goto check_stock_status_menu;
    case 2:
        reset_terminal();
        list_branch_stocks(stocks);
        while(getchar() == ' ');
        getchar();
        goto check_stock_status_menu;
    case 3:
        reset_terminal();
        list_out_of_stocks(stocks);
        while(getchar() == ' ');
        getchar();
        goto check_stock_status_menu;
    case 4:
        return 0;
    default:
        printf("Please enter valid operation!");
        while(getchar() == ' ');
        getchar();
        goto check_stock_status_menu;
        break;
    }

}

// Part 5
int brand_stock_control(char productsfilename[], char stocksfilename[],double filtered_pId_price_stock[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE]){
    // Variable
    char target_brand[MAX_STRING_SIZE];

    reset_terminal();
    // Take target brand from user
    printf("Please enter brand: ");
    scanf("%s", &target_brand);

    // Open files
    FILE *productsfile;
    productsfile = fopen(productsfilename, "r+"); 
    FILE *stocksfile;
    stocksfile = fopen(stocksfilename, "r+"); 
    
    // Variables for read
    char type[5];
    char branch[MAX_STRING_SIZE], name[MAX_STRING_SIZE], brand[MAX_STRING_SIZE];
    int pId, current_stock, sId;
    double price;
    // Variables for filter
    int filteredstock = 0, filteredproduct = 0;

    // Scan until target brand found in products
    while (fscanf(productsfile, "%d,%[^,],%[^,],%[^,],%lf", &pId, &type, &name, &brand, &price) == 5)
    {       
        if (strcmp(brand, target_brand) == 0){
            // If found take datas to array [0] -> pID, [1] -> price, [2+] -> stock
            filtered_pId_price_stock[filteredproduct][0] = (double)pId;
            filtered_pId_price_stock[filteredproduct][1] = price;
            filteredproduct++;
        }   
    }
    // Scan until target pID found in stocks
    while (fscanf(stocksfile, "%d,%d,%[^,],%d", &sId, &pId, &branch, &current_stock) == 4)
    {   
        // Take datas seperate for array to store stocks
        for (int i = 0; i < filteredproduct; i++)
        {
            if (pId == filtered_pId_price_stock[i][0]){
                filtered_pId_price_stock[i][filteredstock + 2] = (double)current_stock;
                filteredstock++;
            }
        }
    }

    // If none of stocks is not fit the filter print
    if (filteredproduct == 0)
    {
        printf("Cannot found any stock.\n");
    }
    else
    {   
        // If found any stock
        int all_stock = 0;
        // Add to all stock
        for (int i = 0; i < filteredproduct; i++)
        {   
            for (int j = 0; j < filteredstock; j++)
            {
                all_stock += (int)filtered_pId_price_stock[i][j + 2];
            }
            // Print
            printf("%d,%.1f,%d\n", (int)filtered_pId_price_stock[i][0], filtered_pId_price_stock[i][1], all_stock);
        }
        
    }

    fclose(productsfile);
    fclose(stocksfile);

}

// Part 6
void stock_report(double filtered_pId_price_stock[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE]){
    
    // Open new report file
    FILE *file;
    file = fopen("report.txt", "w+");
    fprintf(file, "pID, Minimum Stock, Maximum Stock, Median of Stocks\n");

    // Variables
    int min_stock, max_stock;
    double med_stock;
    int all_stock = 0;
    int i = 0, j = 0;

    // Until reads -1(means pID empty) keep reading data
    while (filtered_pId_price_stock[i][0] != -1)
    {   
        // Take base min and max values
        min_stock = filtered_pId_price_stock[i][2];
        max_stock = filtered_pId_price_stock[i][2];
        // Until reads -1(means stocks empty) keep reading data
        while (filtered_pId_price_stock[i][j + 2] != -1)
        {   
            // Add stocks
            all_stock += (int)filtered_pId_price_stock[i][j + 2];
            // If there is change min and max value
            if (filtered_pId_price_stock[i][j + 2] < min_stock) min_stock = filtered_pId_price_stock[i][j + 2];
            if (filtered_pId_price_stock[i][j + 2] > max_stock) max_stock = filtered_pId_price_stock[i][j + 2];
            j++;
        }
        // Find median of stocks
        med_stock = all_stock / j;
        // Print to file
        fprintf(file, "%d, %d, %d, %.1f\n", (int)filtered_pId_price_stock[i][0], min_stock, max_stock, med_stock);
        i++;
    }
    fclose(file);
}    
