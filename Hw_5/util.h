#ifndef _UTIL_H_
#define _UTIL_H_

// Enumeration for Part 2
typedef enum Color{
    RED, GREEN, BLUE, YELLOW, ORANGE
} Color;

void mix_colors(Color color1, Color color2, double *mixed_color);

Color colorMixer(Color color1, Color color2, Color *mix_colors(Color, Color, double*));

int read_color(char c);

void matrix_drawer(int matrix[3][3]);

int check_win_status(int matrix[3][3]);

void letter_frequency_finder();

void mixing_colors();

void tic_tac_toe();

#endif /* _UTIL_H_ */