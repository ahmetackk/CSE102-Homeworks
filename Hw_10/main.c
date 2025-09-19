#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------ Structs ---------------------------------

typedef struct {
    char isbn[20];
    char title[100];
    char author[100];
    int publication_year;
    int reserved_status; 
    struct Book* next;
} Book;

typedef struct {
    int ID;
    char name[100];
    struct Book* borrowed_books;
    struct Student* next;
} Student;

// --------------------------------------------------------------------

// Reset terminal for clean image
void reset_terminal(){
    printf("\033[2J");
    printf("\033[0;0f");
}

// ----------------------------- Functions -----------------------------------

Book *book_list = NULL;
Student *student_list = NULL;

void addBook(char* isbn, char* title, char* author, int publicationYear, int method);
void deleteBook(char* isbn);
void updateBook(char* isbn, char* feature, char* value);
void printBooks();
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice);
void reverseBookList();
void searchBooks(int searchChoice, char* searchValue);
void borrowBook(char* isbn);
void returnBook(char* isbn);
void takeBookList();
void updateBookFile();
void takeStudentList();
void updateStudentFile();
void listStudents();
void listBorrowedBookList();
void listStudentBorrowedBook(int ID);
void updateBorrowedBookFile();
void takeBorrowedBooks();

/*----- MAIN ------*/

int main(){
    // Variables
    int choice;

    char isbn[20];
    char title[100];
    char author[100];
    int publication_year;
    int method;

    char feature[20];
    char value[100];

    int filterChoice;
    char filter[100];
    int sortChoice;

    int ID;
    
    int reserved_status; 

    // Take datas from files
    takeBookList();
    takeStudentList();
    takeBorrowedBooks();

    // Main Menu
    main_menu:
    reset_terminal();
    printf("Welcome to the Library System\n");
    printf("1. Book operations\n2. Student operations\n0. Exit\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        book_menu:
        reset_terminal();
        printf("Book Menu\n");
        printf("1. List books\n2. Add book\n3. Delete book\n4. Update book\n5. Filter and sort books\n6. Reverse book list\n0. Back\n");
        scanf("%d", &choice);

        reset_terminal();
        switch (choice)
        {
        case 1:
            printBooks();
            break;
        case 2:
            printf("Please enter book to add (isbn title author publicationyear): ");
            scanf("%s %s %s %d", &isbn, &title, &author, &publication_year);
            printf("Please enter the method (0 for FIFO, 1 for LIFO): ");
            scanf("%d", &method);
            addBook(isbn, title, author, publication_year, method);
            break;
        case 3:
            printf("Please enter isbn of the book for delete: ");
            scanf(" %s", &isbn);
            deleteBook(isbn);
            break;
        case 4:
            printf("Please enter isbn of the book: ");
            scanf(" %s", &isbn);
            printf("Please enter the feature you want to update: ");
            scanf(" %s", &feature);
            printf("Please enter the new value: ");
            scanf(" %s", &value);
            updateBook(isbn, feature, value);
            break;
        case 5:
            printf("Please enter filter choice (0 for author, 1 for publication year): ");
            scanf("%d", &filterChoice);
            printf("Please enter the filter: ");
            scanf(" %s", &filter);
            printf("Please enter sort choice (0 for title, 1 for author, 2 for publication year): ");
            scanf("%d", &sortChoice);
            filterAndSortBooks(filterChoice, filter, sortChoice);
            break;
        case 6:
            reverseBookList();
            break;
        case 0:
            goto main_menu;
        default:
            break;
        }

        updateBookFile();
        while(getchar() == ' ');
        getchar();
        goto book_menu;
    case 2:
        student_menu:
        reset_terminal();
        printf("Student Menu\n");
        printf("1. List all students\n2. List borrowed books\n3. Borrow book\n4. Return book\n0. Back\n");
        scanf("%d", &choice);

        Student *shead;
        Book *studentsBookList;
        Book *booklisthead;

        reset_terminal();
        switch (choice)
        {
        case 1:
            listStudents();
            break;
        case 2:
            borrowed_menu:
            reset_terminal();
            printf("1. List all borrowed books\n2. List student's borrowed books\n0. Back\n");
            scanf("%d", &choice);

            reset_terminal();
            switch (choice)
            {
            case 1:
                listBorrowedBookList();
                break;
            case 2:
                reset_terminal();
                printf("Please enther student's ID: ");
                scanf("%d", &ID);

                listStudentBorrowedBook(ID);
                break;
            case 0:
                goto student_menu;
            default:
                break;
            }

            while(getchar() == ' ');
            getchar();
            goto borrowed_menu;
        case 3:
            printf("Enter student ID: ");
            scanf("%d", &ID);
            printf("Enter isbn of the book: ");
            scanf(" %s", &isbn);
            borrowBook(&isbn);

            // Find the student from taken ID
            shead = student_list;
            while (shead != NULL && shead->ID != ID) shead = shead->next;

            studentsBookList = shead->borrowed_books;
            booklisthead = book_list;

            // Find the book from taken isbn
            while (booklisthead != NULL )
            {   
                if (strcmp(booklisthead->isbn, isbn) == 0)
                {
                    strcpy(isbn, booklisthead->isbn);
                    strcpy(title, booklisthead->title);
                    strcpy(author, booklisthead->author);
                    publication_year = booklisthead->publication_year;
                    booklisthead->reserved_status = 1;
                }
                booklisthead = booklisthead->next;
            }
            
            // Create new book and copy found book
            Book *new_book = (Book*)malloc(sizeof(Book));
            strcpy(new_book->isbn, isbn);
            strcpy(new_book->title, title);
            strcpy(new_book->author, author);
            new_book->publication_year = publication_year;
            new_book->reserved_status = 1;
            new_book->next = NULL;

            // Add to students borrowed books
            if (studentsBookList == NULL)
            {
                shead->borrowed_books = new_book;
            }
            else 
            {   
                Book *temp = studentsBookList;
                while (temp->next != NULL) temp = temp->next;
                temp->next = new_book;
            }

            // Update files after changes
            updateBookFile();
            updateBorrowedBookFile();
            break;
        case 4:
            printf("Enter student ID: ");
            scanf("%d", &ID);
            printf("Enter isbn of the book: ");
            scanf(" %s", &isbn);
            returnBook(&isbn);

            // Find the student from taken ID
            shead = student_list;
            while (shead != NULL && shead->ID != ID) shead = shead->next;

            booklisthead = shead->borrowed_books;

            // Find the book from taken isbn
            while (booklisthead != NULL && strcmp(booklisthead->isbn, isbn) != 0) booklisthead = booklisthead->next;

            // Delete book from students borrowed book
            Book *curr, *prev;
            curr = booklisthead;
            prev = booklisthead;

            while (curr != NULL && strcmp(curr->isbn, isbn) != 0)
            {   
                prev = curr;
                curr = curr->next;
            }

            if (curr != NULL)
            {
                if (curr != prev)
                {
                    prev->next = curr->next;
                }
                else
                {
                    booklisthead = curr->next;
                }
                free(curr);
            }

            // Update files after changes
            updateBookFile();
            updateBorrowedBookFile();
            break;
        case 0:
            goto main_menu;
        default:
            break;
        }

        while(getchar() == ' ');
        getchar();
        goto student_menu;
    case 0:
        printf("Exit...\n");
        break;
    default:
        break;
    }

    return 0;
}


// -------------------------- Book Functions -------------------------------------


void addBook(char* isbn, char* title, char* author, int publicationYear, int method){
    // Create new book with taken parameters
    Book *new_book = (Book*)malloc(sizeof(Book));
    strcpy(new_book->isbn, isbn);
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    new_book->publication_year = publicationYear;
    new_book->reserved_status = 0;
    new_book->next = NULL;

    // Add book to the book list
    if (book_list == NULL)
    {
        book_list = new_book;
    }
    else if (method == 0)
    {   
        Book *temp = book_list;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_book;
    }
    else
    {
        new_book->next = book_list;
        book_list = new_book;
    }

    printf("Book added!\n");
}

void deleteBook(char* isbn){
    Book *curr, *prev;
    curr = book_list;
    prev = book_list;

    // Find book in the book list
    while (curr != NULL && strcmp(curr->isbn, isbn) != 0)
    {   
        prev = curr;
        curr = curr->next;
    }

    // Delete if book is found
    if (curr != NULL)
    {
        if (curr != prev)
        {
            prev->next = curr->next;
        }
        else
        {
            book_list = curr->next;
        }
        free(curr);
        printf("Book deleted succesfully!\n");
    }
    else
    {
        printf("Book is not found!\n");
    }
    
}

void updateBook(char* isbn, char* feature, char* value){
    Book *temp;
    temp = book_list;

    // Find book
    while (temp != NULL && strcmp(temp->isbn, isbn) != 0) temp = temp->next;
    
    // If book is found
    if (temp != NULL)
    {   
        // Update along to the taken feature
        if (strcmp(feature, "title") == 0)
        {
            strcpy(temp->title, value);
        }
        else if (strcmp(feature, "author") == 0)
        {
            strcpy(temp->author, value);
        }
        else if (strcmp(feature, "publication year") == 0)
        {
            temp->publication_year = value;
        }
    }
}

void printBooks(){
    // Print books to terminal
    Book* head = book_list;
    while (head != NULL)
    {   
        printf("%s, %s, %s, %d, ", head->isbn, head->title, head->author, head->publication_year);
        if (head->reserved_status) printf("reserved\n");
        else printf("not reserved\n");
        head = head->next;
    }
}


/* Author and title sort part is not working like i want thats */
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice){
    Book *temp;
    temp = book_list;

    Book *filtered_list = NULL;
    Book *filtered_list_head;


    // Filter choice 0 for author, 1 for publication year
    switch (filterChoice)
    {
    case 0:
        while (temp != NULL)
        {   
            if (strcmp(temp->author, filter) == 0)
            {
                Book* filtered_book = (Book*)malloc(sizeof(Book));
                strcpy(filtered_book->isbn, temp->isbn);
                strcpy(filtered_book->title, temp->title);
                strcpy(filtered_book->author, temp->author);
                filtered_book->publication_year = temp->publication_year;
                filtered_book->reserved_status = temp->reserved_status;
                filtered_book->next = NULL;

                if (filtered_list == NULL)
                {
                    filtered_list = filtered_book;
                    filtered_list_head = filtered_book;
                }
                else
                {   
                    Book *temp2 = filtered_list_head;
                    while (temp2->next != NULL) temp2 = temp2->next;
                    temp2->next = filtered_book;
                }
            }
            temp = temp->next;
        }
        break;
    case 1:
        while (temp != NULL)
        {   
            if (temp->publication_year == atoi(filter))
            {
                Book *filtered_book = (Book*)malloc(sizeof(Book));
                strcpy(filtered_book->isbn, temp->isbn);
                strcpy(filtered_book->title, temp->title);
                strcpy(filtered_book->author, temp->author);
                filtered_book->publication_year = temp->publication_year;
                filtered_book->reserved_status = temp->reserved_status;
                filtered_book->next = NULL;

                if (filtered_list == NULL)
                {
                    filtered_list = filtered_book;
                    filtered_list_head = filtered_book;
                }
                else
                {   
                    Book *temp2 = filtered_list_head;
                    while (temp2->next != NULL) temp2 = temp2->next;
                    temp2->next = filtered_book;
                }
            }
            temp = temp->next;
        }
        break;
    default:
        break;
    }

    // Take filtered list
    filtered_list = filtered_list_head;

    Book *curr;
    Book *next;

    char isbn[20];
    char title[100];
    char author[100];
    int publication_year;
    int reserved_status; 

    // Sort 0 for title, 1 for author, 2 for publication year 
    switch (sortChoice)
    {
    case 0:
        curr = filtered_list;
        int arraylen = 0;
        int len1, len2;

        while (curr != NULL)
        {   
            arraylen++;
            curr = curr->next;
        }

        curr = filtered_list;
        int switch_flag;
        
        for (int i = 0; i < arraylen - 1; i++)
        {
            for (int j = 0; j < arraylen - 1; j++)
            {   
                next = curr->next;
                len1 = strlen(curr->title);
                len2 = strlen(next->title);

                if (len1 > len2)
                {
                    int i = 0;
                    while (i < len2)
                    {
                        if (curr->title[i] == next->title[i]) i++;
                        else if (curr->title[i] > next->title[i])
                        {
                            switch_flag = 1;
                            break;
                        }
                        else if (i == len2 - 1)
                        {
                            switch_flag = 1;
                            break;
                        }
                        else
                        {
                            switch_flag = 0;
                            break;
                        }
                    }
                }
                else
                {
                    int i = 0;
                    while (i < len1)
                    {
                        if (curr->title[i] == next->title[i]) i++;
                        else if (curr->title[i] > next->title[i])
                        {
                            switch_flag = 1;
                            break;
                        }
                        else if (i == len1 - 1)
                        {
                            switch_flag = 1;
                            break;
                        }
                        else
                        {
                            switch_flag = 0;
                            break;
                        }
                    }
                }

                if (switch_flag)
                {
                    strcpy(isbn, curr->isbn);
                    strcpy(title, curr->title);
                    strcpy(author, curr->author);
                    publication_year = curr->publication_year;
                    reserved_status = curr->reserved_status;

                    strcpy(curr->isbn, next->isbn);
                    strcpy(curr->title, next->title);
                    strcpy(curr->author, next->author);
                    curr->publication_year = next->publication_year;
                    curr->reserved_status = next->reserved_status;

                    strcpy(next->isbn, isbn);
                    strcpy(next->title, title);
                    strcpy(next->author, author);
                    next->publication_year = publication_year;
                    next->reserved_status = reserved_status;
                }
                else curr = curr->next;
            }
            curr = filtered_list;
        }
        break;
    case 1:
        curr = filtered_list;
        int arraylen = 0;
        int len1, len2;

        while (curr != NULL)
        {   
            arraylen++;
            curr = curr->next;
        }

        curr = filtered_list;
        int switch_flag;
        
        for (int i = 0; i < arraylen - 1; i++)
        {
            for (int j = 0; j < arraylen - 1; j++)
            {   
                next = curr->next;
                len1 = strlen(curr->author);
                len2 = strlen(next->author);

                if (len1 > len2)
                {
                    int i = 0;
                    while (i < len2)
                    {
                        if (curr->author[i] == next->author[i]) i++;
                        else if (curr->author[i] > next->author[i])
                        {
                            switch_flag = 1;
                            break;
                        }
                        else if (i == len2 - 1)
                        {
                            switch_flag = 1;
                            break;
                        }
                        else
                        {
                            switch_flag = 0;
                            break;
                        }
                    }
                }
                else
                {
                    int i = 0;
                    while (i < len1)
                    {
                        if (curr->author[i] == next->author[i]) i++;
                        else if (curr->author[i] > next->author[i])
                        {
                            switch_flag = 1;
                            break;
                        }
                        else if (i == len1 - 1)
                        {
                            switch_flag = 1;
                            break;
                        }
                        else
                        {
                            switch_flag = 0;
                            break;
                        }
                    }
                }

                if (switch_flag)
                {
                    strcpy(isbn, curr->isbn);
                    strcpy(title, curr->title);
                    strcpy(author, curr->author);
                    publication_year = curr->publication_year;
                    reserved_status = curr->reserved_status;

                    strcpy(curr->isbn, next->isbn);
                    strcpy(curr->title, next->title);
                    strcpy(curr->author, next->author);
                    curr->publication_year = next->publication_year;
                    curr->reserved_status = next->reserved_status;

                    strcpy(next->isbn, isbn);
                    strcpy(next->title, title);
                    strcpy(next->author, author);
                    next->publication_year = publication_year;
                    next->reserved_status = reserved_status;
                }
                else curr = curr->next;
            }
            curr = filtered_list;
        }
        break;

    case 2:
        curr = filtered_list;
        int len = 0;

        while (curr != NULL)
        {   
            len++;
            curr = curr->next;
        }

        curr = filtered_list;
        
        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < len - 1; j++)
            {   
                next = curr->next;
                if (curr->publication_year < next->publication_year)
                {
                    strcpy(isbn, curr->isbn);
                    strcpy(title, curr->title);
                    strcpy(author, curr->author);
                    publication_year = curr->publication_year;
                    reserved_status = curr->reserved_status;

                    strcpy(curr->isbn, next->isbn);
                    strcpy(curr->title, next->title);
                    strcpy(curr->author, next->author);
                    curr->publication_year = next->publication_year;
                    curr->reserved_status = next->reserved_status;

                    strcpy(next->isbn, isbn);
                    strcpy(next->title, title);
                    strcpy(next->author, author);
                    next->publication_year = publication_year;
                    next->reserved_status = reserved_status;
                }
                else curr = curr->next;
            }
            curr = filtered_list;
        }
        break;
    default:
        break;
    }
    
    while (filtered_list != NULL)
    {
        printf("%s,%s,%s\n", filtered_list->isbn, filtered_list->title, filtered_list->author);
        filtered_list = filtered_list->next;
    }
    
}

void reverseBookList(){
    // If book list has 1 length
    if (book_list == NULL || book_list->next == NULL) return;
    
    Book* prev = NULL;
    Book* current = book_list;
    Book* next;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    book_list = prev;
    printf("Book list reversed!\n");
}

void searchBooks(int searchChoice, char* searchValue){
    Book *head;
    head = book_list;

    int found_flag = 0;

    switch (searchChoice)
    {
    // ISBN
    case 0:
        while (head != NULL)
        {
            if (strcmp(head->isbn, searchValue) == 0)
            {
                printf("%s, %s, %s, %d, ", head->isbn, head->title, head->author, head->publication_year);
                if (head->reserved_status) printf("reserved\n");
                else printf("not reserved\n");
                found_flag = 1;
            }
            head = head->next;
        }
        break;
    // author
    case 1:
        while (head != NULL)
        {
            if (strcmp(head->author, searchValue) == 0)
            {
                printf("%s, %s, %s, %d, ", head->isbn, head->title, head->author, head->publication_year);
                if (head->reserved_status) printf("reserved\n");
                else printf("not reserved\n");
                found_flag = 1;
            }
            head = head->next;
        }
        break;
    // title
    case 2:
        while (head != NULL)
        {
            if (strcmp(head->title, searchValue) == 0)
            {
                printf("%s, %s, %s, %d, ", head->isbn, head->title, head->author, head->publication_year);
                if (head->reserved_status) printf("reserved\n");
                else printf("not reserved\n");
                found_flag = 1;
            }
            head = head->next;
        }
        break;
    default:
        break;
    }

    if (found_flag == 0)
    {
        printf("Book is not found!\n");
    }
}

void borrowBook(char* isbn){
    // take book list
    Book *head;
    head = book_list;

    int found_flag = 0;

    while (head != NULL)
    {   
        // If book is find make its reserved status 1
        if (strcmp(head->isbn, isbn) == 0)
        {
            head->reserved_status = 1;
            found_flag = 1;
        }
        head = head->next;
    }

    if (found_flag == 0)
    {
        printf("Book is not found!\n");
    }
}

void returnBook(char* isbn){
    // take book list
    Book *head;
    head = book_list;

    int found_flag = 0;

    while (head != NULL)
    {
        // If book is find make its reserved status 0
        if (strcmp(head->isbn, isbn) == 0)
        {
            head->reserved_status = 0;
            found_flag = 1;
        }
        head = head->next;
    }

    if (found_flag == 0)
    {
        printf("Book is not found!\n");
    }
}

void takeBookList(){
    // Open file
    FILE *file;
    file = fopen("books.txt", "r");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    char isbn[20];
    char title[100];
    char author[100];
    int publication_year;
    int reserved_status; 

    // Scan until the end
    while (fscanf(file, "%s %s %s %d %d ", &isbn, &title, &author, &publication_year, &reserved_status) == 5)
    {
        // Create and add books to the linked list
        Book *new_book = (Book*)malloc(sizeof(Book));
        strcpy(new_book->isbn, isbn);
        strcpy(new_book->title, title);
        strcpy(new_book->author, author);
        new_book->publication_year = publication_year;
        new_book->reserved_status = reserved_status;
        new_book->next = NULL;

        if (book_list == NULL)
        {
            book_list = new_book;
        }
        else 
        {   
            Book *temp = book_list;
            while (temp->next != NULL) temp = temp->next;
            temp->next = new_book;
        }

    }

    fclose(file);
}

void updateBookFile(){
    // Open file
    FILE *file;
    file = fopen("books.txt", "w+");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    Book *head = book_list;

    // Update file 
    while (head != NULL)
    {
        fprintf(file, "%s %s %s %d %d\n", head->isbn, head->title, head->author, head->publication_year, head->reserved_status);
        head = head->next;
    }

    fclose(file);
    
}

// ------------------------------ Student Functions -----------------------------------

void takeStudentList(){
    // Take student list from file
    FILE *file;
    file = fopen("students.txt", "r");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    int ID;
    char name[20];

    while (fscanf(file, "%d %s ", &ID, &name) == 2)
    {
        Student *new_student = (Student*)malloc(sizeof(Student));
        strcpy(new_student->name, &name);
        new_student->ID = ID;
        new_student->borrowed_books = NULL;
        new_student->next = NULL;
        
        if (student_list == NULL)
        {   
            student_list = new_student;
        }
        else 
        {   
            Student *temp = student_list;
            while (temp->next != NULL) temp = temp->next;
            temp->next = new_student;
        }
    }

    fclose(file);
}

void updateStudentFile(){
    FILE *file;
    file = fopen("students.txt", "r");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    Student *head = student_list;

    while (head != NULL)
    {
        fprintf(file, "%d %s\n", head->ID, head->name);
        head = head->next;
    }

    fclose(file);
    
}

void listStudents(){
    Student *head = student_list;
    while (head != NULL)
    {   
        printf("%d, %s\n", head->ID, head->name);
        head = head->next;
    }
}

void listBorrowedBookList(){
    FILE *file;
    file = fopen("borrowedbooks.txt", "r");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    int ID;
    char isbn[20];
    char title[100];
    char author[100];
    int publication_year;

    while (fscanf(file, "%d %s %s %s %d", &ID, &isbn, &title, &author, &publication_year) == 5)
    {
        printf("%d, %s, %s, %s, %d\n", ID, isbn, title, author, publication_year);
    }
    
    fclose(file);
    
}

void listStudentBorrowedBook(int ID){
    Student *head = student_list;
    while (head != NULL && head->ID != ID) head = head->next;

    Book *studentBookList = head->borrowed_books;
    while (studentBookList != NULL)
    {
        printf("%s, %s, %s, %d\n", studentBookList->isbn, studentBookList->title, studentBookList->author, studentBookList->publication_year);
        studentBookList = studentBookList->next;
    }
}

void updateBorrowedBookFile(){
    FILE *file;
    file = fopen("borrowedbooks.txt", "w+");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    Student *head = student_list;
    Book *books;

    while (head != NULL)
    {
        if (head->borrowed_books != NULL)
        {   
            books = head->borrowed_books;
            while (books != NULL)
            {   
                fprintf(file, "%d %s %s %s %d\n", head->ID, books->isbn, books->title, books->author, books->publication_year);
                books = books->next;
            }
        }
        head = head->next;
    }

    fclose(file);

}

void takeBorrowedBooks(){
    // Open file
    FILE *file;
    file = fopen("borrowedbooks.txt", "r");

    if (file == NULL)
    {
        printf("File can not opened!\n");
        return;
    }

    Student *head = student_list;
    Book *books;

    int ID;
    char isbn[20];
    char title[100];
    char author[100];
    int publication_year;

    // Scan file to the end
    while (fscanf(file, "%d %s %s %s %d", &ID, &isbn, &title, &author, &publication_year) == 5)
    {   
        // Scan the student list
        while(head != NULL)
        {
            books = head->borrowed_books;
            // If id matches add borrowed books
            if (head->ID == ID)
            {
                Book *new_book = (Book*)malloc(sizeof(Book));
                strcpy(new_book->isbn, isbn);
                strcpy(new_book->title, title);
                strcpy(new_book->author, author);
                new_book->publication_year = publication_year;
                new_book->reserved_status = 1;
                new_book->next = NULL;

                if (books == NULL)
                {
                    head->borrowed_books = new_book;
                }
                else 
                {   
                    Book *temp = books;
                    while (temp->next != NULL) temp = temp->next;
                    temp->next = new_book;
                }
            }
            head = head->next;
        }
        
    }

    fclose(file);
}


