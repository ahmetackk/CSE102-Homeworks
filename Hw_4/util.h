#ifndef _UTIL_H_
#define _UTIL_H_

void reset_terminal();

void space(int a);

const char* choice_string(int a);

const char* menu_element_string(int a);

void read_file();

int rpc_win_statue(int choice, int computer_choice);

void rock_paper_scissors();

void order_menu();

#endif /* _UTIL_H_ */