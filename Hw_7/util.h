#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 12

void reset_terminal();

void *string_copy(const char * strcopy, char * str);

int ignore(const char * word, char ignore_word[][MAX_WORD_SIZE], int ignore_word_number);

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]);

int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]);

double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, int reverse);

int histogram(const char words[][MAX_WORD_SIZE], const char closestuserwords[][MAX_WORD_SIZE], const int occurrences[], const int word_number);

int dict_word_check(const char word[], const char dict[][MAX_WORD_SIZE], int dict_word_number);

int find_occurence(const char * text_file, const char target_word[]);

#endif /* _UTIL_H_ */