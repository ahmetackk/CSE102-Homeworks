#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"

void addBook(char* isbn, char* title, char* author, int publicationYear, int method){
    Book *new_book = (Book*)malloc(sizeof(Book));
    strcpy(new_book->isbn, isbn);
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    new_book->publication_year = publicationYear;
    new_book->reserved_status = 0;
    new_book->next = NULL;

    if (book_list == NULL)
    {
        book_list = new_book;
    }
    else if (method == 0)
    {   
        Book *temp = book_list;
        while (temp != NULL) temp = temp->next;
        temp->next = new_book;
    }
    else
    {
        new_book->next = book_list;
        book_list = new_book;
    }

    printf("Book added!\n");
}
