#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_ARRAY_SIZE 100
#define MAX_STRING_SIZE 20

void reset_terminal();

void add_product(char filename[]);

void delete_product(char filename[]);

void update_product(char filename[]);

void add_new_stock(char filename[]);

void delete_stock(char filename[]);

void update_stock(char filename[]);

void list_products(char filename[]);

void filter_products(char filename[]);

void list_product_stock_branch(char filename[]);

void list_branch_stocks(char filename[]);

void list_out_of_stocks(char filename[]);

int file_operations(char products[], char stocks[]);

int search_product(char file[]);

int check_stock_status(char stocks[]);

int brand_stock_control(char productsfilename[], char stocksfilename[],double filtered_pId_price_stock[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE]);

void stock_report(double filtered_pId_price_stock[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE]);

#endif /* _UTIL_H_ */