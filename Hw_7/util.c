#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "util.h"

#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 12

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

// Reset terminal for clean image
void reset_terminal(){
    printf("\033[2J");
    printf("\033[0;0f");
}

// String copy function like strcpy()
void *string_copy(const char * strcopy, char * str){

    while (*strcopy) 
    {
        *str = *strcopy;
        str++;
        strcopy++;
    }

    *str = '\0';
}

// Ignore function for read_text
int ignore(const char * word, char ignore_word[][MAX_WORD_SIZE], int ignore_word_number){

    int n = 0;
    for (int i = 0; i < ignore_word_number; i++)
    {   
        // If word is same as ignore word then return 1
        if (strcmp(word, ignore_word[i]) == 0)
        {
            n = 1;
        }
    }
    return n;
}

// Draw hist 
void draw_hist(int occurence){
    
    // If there is not occurence with closest word
    if (occurence == 0)
    {
        printf("No matches!");
    }
    // If there is not occurence and the word is not in the dictionary
    else if(occurence == -1)
    {
        printf("No matches also the word is not in dictionary!");
    }
    // If there is an occurence 
    else{
        int a = occurence;
        // Find mod 20 first
        if (occurence > 20)
        {
            a = occurence % 20;
        }
        // Then print
        for (int i = 0; i < a; i++)
        {
            printf("*");
        }
    }
    printf("\n--------------------------------------------------");
}

// Find occurence takes text files name and target word then returns words occurence
int find_occurence(const char * text_file, const char target_word[]){
    // Open file 
    FILE *text;
    text = fopen(text_file, "r");

    if (text == NULL)
    {
        printf("File cannot opened!");
        return -1;
    }
    
    // Variables
    int word_number = 0, dict_index = 0;
    char c, word[MAX_WORD_SIZE];
    int occurence = 0;

    // Read words
    int i = 0;
    c = getc(text);
    while (c != EOF)
    {   
        // If taken char is a letter, "," or "'"  take this to word
        if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || c == 39 || c == 96) 
        {      
            word[i] = c;
            i++;
        }
        // If taken char is another then finish the word
        else{
            word[i] = '\0';
            if (strcmp(word, target_word) == 0)
            {   
                occurence++;
            }
            word_number++;
            memset(word, 0, sizeof(word));
            i = 0;
            
        }
        c = getc(text);
    }

    fclose(text);

    return occurence;     
}

// Check word is in the dictionary
int dict_word_check(const char word[], const char dict[][MAX_WORD_SIZE], int dict_word_number){
    
    for (int i = 0; i < dict_word_number; i++)
    {   
        // If dictionary word same as word return 1 
        if (strcmp(word, dict[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

// Reads dict and reads dictionary word to dict array, returns dictionary words number
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
    // File open
    FILE *file;
    file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("File cannot opened!");
        return -1;
    }

    // Take first line for number of words and vectors size
    int wordnumber, vectorsize;
    fscanf(file, "num_word=%d, vector_size=%d", &wordnumber, &vectorsize);

    double dictionaryvectors[wordnumber + 10][vectorsize + 10];

    int dictindex = 0;

    // Firstly read word
    while (fscanf(file, "%s", &dict[dictindex]) == 1)
    {   
        // Then read vectors 
        for (int i = 0; i < vectorsize; i++)
        {
            fscanf(file, "%lf", &dictionaryvectors[dictindex][i]);
        }
        dictindex++;
    }

    fclose(file);

    if(dictindex == 0) return -1;
    else return dictindex;     
    
}

// Reads text with ignoring words from ignore file then returns number of words in text
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]){
    // Files open
    FILE *text;
    text = fopen(text_file, "r");
    FILE *ignore;
    ignore = fopen(ignore_file, "r");

    if (text == NULL || ignore == NULL)
    {
        printf("File cannot opened!");
        return -1;
    }
    // Variables
    int word_number = 0, dict_index = 0, filtered_word = 0;
    char c, word[MAX_WORD_SIZE], ignore_word[MAX_WORD_COUNT][MAX_WORD_SIZE];

    // Read ignore file
    int ignorecounter = 0;
    while (fscanf(ignore, "%s", &ignore_word[ignorecounter]) == 1)
    {
        ignorecounter++;
    }

    // Read text file
    int i = 0;
    c = getc(text);
    while (c != EOF)
    {   
        // If there is a punctuation mark
        if (c != '.' && c != '/' && c != ':' && c != ';' && c != '\\' && c != '"')
        {     
            // If taken char is space or "-" finish word
            if (c == '-' || c == ' ' || c == '\n'){
                word[i] = '\0';
                // If "-" take word to filtered words
                if (c == '-')
                {   
                    string_copy(words[filtered_word], word);
                    filtered_word++;
                }
                else word_number++;
                memset(word, 0, sizeof(word));
                i = 0;
            }
            // Else take char to word
            else{
                word[i] = c;
                i++;
            }
        }
        c = getc(text);
    }

    // Close files
    fclose(text);
    fclose(ignore);

    printf("Ignored: %d\n", filtered_word);
    if(word_number == 0) return -1;
    else return word_number;     
}

// If reverse is 0 controls  w1 and w2 are same, else looks w1's closest word 
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, int reverse){
    // Open file
    FILE *dictionary;
    dictionary = fopen("dictionary.txt", "r");
    
    if (dictionary == NULL){
        printf("File cannot opened.");
        return -1;
    }

    // Read first line for numbers of word and vectors size 
    int wordnumber, vectorsize;
    fscanf(dictionary, "num_word=%d, vector_size=%d", &wordnumber, &vectorsize);

    double dictionaryvectors[wordnumber + 10][vectorsize + 10];

    // First scan dictionary word and take words vector
    int dictindex = 0;
    while (fscanf(dictionary, "%s", &dict[dictindex]) == 1)
    {   
        for (int i = 0; i < vectorsize; i++)
        {
            fscanf(dictionary, "%lf", &dictionaryvectors[dictindex][i]);
        }
        dictindex++;
    }
    // Close file
    fclose(dictionary);

    // If reverse is 0 look words are same 
    if (reverse == 0)
    {   
        if (strcmp(w1, w2) == 0) return 0;
        else{
            int w1_index, w2_index;

            for (int i = 0; i < wordnumber; i++){
                if (strcmp(dict[i], w1) == 0) w1_index = i;
                if (strcmp(dict[i], w2) == 0) w2_index = i;
            }

            double total_diss = 0.0;

            for (int i = 0; i < vectorsize; i++)
            {
                total_diss += pow(dictionaryvectors[w1_index][i] - dictionaryvectors[w2_index][i], 2);
            }
            
            return total_diss;
        }
    }
    // Else look for closest word
    else{
        double temp_diss = 0.0, min_diss = 1000;
        int w_index;

        // First find words dictionary index for vectors
        for (int i = 0; i < wordnumber; i++){
                if (strcmp(dict[i], w1) == 0){
                w_index = i;
                }
        }

        for (int i = 0; i < wordnumber; i++)
        {     
            // If word is not same as w1 look for dissimilarity
            if (i != w_index)
            {   
                for (int j = 0; j < vectorsize; j++)
                {   
                    temp_diss +=  pow((dictionaryvectors[w_index][j] - dictionaryvectors[i][j]), 2);
                }
                temp_diss = temp_diss / vectorsize;
                
                // If distance is lower then minimum take word
                if (temp_diss < min_diss){
                    min_diss = temp_diss;  
                    string_copy(dict[i], w2);
                }
                temp_diss = 0.0;
            }
        }
        
        // If min distance is lower than threshold return
        if (min_diss <= threshold)
        {   
            return min_diss;
        }
        else{
            return -1;
        } 
    }
    
}

// Histogram for occurences
int histogram(const char words[][MAX_WORD_SIZE], const char closestuserwords[][MAX_WORD_SIZE], const int occurrences[], const int word_number){
    int scale;
    
    for (int i = 0; i < word_number; i++)
    {   
        // First find sacale
        scale = (int)(occurrences[i] / 20);
        if (scale != 0)
        {
            printf("Scale: %d\n", scale);
        }
        // If word has closeset word print with closest word
        if (closestuserwords[i][0] != 'x')
        {
            printf("%-12s -> %-12s \t", words[i], closestuserwords[i]);
        }
        // Else just print word
        else{
            printf("%-12s                 \t", words[i]);
        }
        // Draw *'s
        draw_hist(occurrences[i]);
        printf("\n");
    }
}
