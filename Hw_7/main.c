#include <stdio.h>
#include <string.h>
#include "util.h"

#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 12
#define THRESHOLD 30

/*----- MAIN ------*/

int main(){
    // Arrays 
    char dictionaryfilename[] = "dictionary.txt";
    char ignorefilename[] = "ignore.txt";
    char inputfilename[] = "input.txt";
    char userwords[MAX_WORD_COUNT][MAX_WORD_SIZE];
    char closestuserwords[MAX_WORD_COUNT][MAX_WORD_SIZE] = {0};
    char c[MAX_WORD_COUNT * (MAX_WORD_SIZE + 1)];
    char dict[3000][MAX_WORD_SIZE];

    // Take words from user
    reset_terminal();
    printf("Enter word(s): ");
    fgets(c ,MAX_WORD_COUNT * (MAX_WORD_SIZE + 1), stdin);
    
    // Seperate words to an array
    int i = 0, userwordnumber = 0, j = 0;
    while (c[j] != NULL)
    {   
        if (c[j] == ' ' || c[j] == '\n')
        {   
            userwords[userwordnumber][i] = '\0';
            userwordnumber++;
            i = 0;
            j++;
        }
        else{
            userwords[userwordnumber][i] = c[j];
            i++;
            j++;
        }
        
    }

    // Read dict file
    int dict_word_number = read_dict(&dictionaryfilename, &dict);

    int number_found = 0;
    int occurences[MAX_WORD_COUNT] = {0};
    char closest_word[MAX_WORD_SIZE];
    // Find occurances
    for (int i = 0; i < userwordnumber; i++)
    {    
        closestuserwords[i][0] = 'x';
        // If words occurence is 0 then try to find its closest words occurence else just find words occurence
        if (find_occurence(inputfilename, userwords[i]) == 0)
        {   
            // Check word is int the directory
            if (dict_word_check(userwords[i], dict, dict_word_number))
            {   
                // If the word has similiar word 
                if(dissimilarity(userwords[i], closest_word, dict, THRESHOLD, 1) != -1){
                    // Find occurence of word
                    if (find_occurence(inputfilename, closest_word) == 0)
                    {   
                        occurences[i] = 0;
                    }
                    else{
                        // If similiar word has occurence then take the closest word to an array
                        string_copy(closest_word, closestuserwords[i]);
                        occurences[i] = find_occurence(inputfilename, closest_word);
                    }
                }
                // If its not 
                else{
                    occurences[i] = 0;
                }
            }
            // If word is not in the dictionary return -1 
            else{
                occurences[i] = -1;
            }
        }
        else{
            occurences[i] = find_occurence(inputfilename, userwords[i]);
        }        
    }

    // Print histogram
    histogram(userwords, closestuserwords, occurences,userwordnumber);

    return 0;
}