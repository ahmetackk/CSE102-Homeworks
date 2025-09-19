#ifndef _UTIL_H_
#define _UTIL_H_

void reset_terminal();

void draw_room(int size, int d_y, int d_x, int c_y, int c_x);

int control_stat(int d_y, int d_x, int c_y, int c_x);

void game(int size, int d_y, int d_x, int c_y, int c_x, int step_counter);

#endif /* _UTIL_H_ */